#include "arplistener.h"
#include <iostream>
#include <time.h>

const std::string ArpListener::k_arp_filter = "arp";

void* run_listener(void *data)
{
  ArpListener *listener = reinterpret_cast< ArpListener* >(data);
  listener->listenerThread();
  return NULL;
}

ArpListener::ArpListener():running_(false), cache_(NULL), arpFilter_( k_arp_filter )
{
}

ArpListener::~ArpListener()
{
  MutexLocker lock2( alertMutex_ );
  std::map< std::string, std::pair< bool, Condition* > >::iterator itr;
  for( itr = alerts_.begin(); itr != alerts_.end(); ++itr )
  {
    delete itr->second.second;
  }

  //stop threads
  MutexLocker lock( runningMutex_ );
  if( running_ )
  {
    sniffer_.stop();
    listenerThread_.stop();
  }

}

void ArpListener::start()
{
  MutexLocker lock( runningMutex_ );
  if( running_ )
    return;
  running_ = true;
  lock.unlock();
  listenerThread_.setStartRoutine( run_listener );
  listenerThread_.start( this );
  timespec sleeptime; //to ensure the sniffer threads are up
  sleeptime.tv_sec = 1;
  sleeptime.tv_nsec = 0;
  nanosleep( &sleeptime, NULL );
}

void ArpListener::stop()
{
  MutexLocker lock( runningMutex_ );
  if( !running_ )
    return;
  listenerThread_.stop();
  running_ = false;
}

bool ArpListener::isRunning() const
{
  MutexLocker lock( runningMutex_ );
  return running_;
}

void ArpListener::setCache(ArpCache *cache)
{
  cache_ = cache;
}

void ArpListener::listenerThread()
{
  if( arpFilter_.size() == 0 || device_.size() == 0 )
  {
    MutexLocker lock( runningMutex_ );
    running_ = false;
    return;
  }

  sniffer_.setFilter( arpFilter_ );
  sniffer_.setInputDevice(device_);
  sniffer_.start();

  while( true )
  {
    Packet p = sniffer_.popPacket();
    if( p.appSize() > 0 && p.appIs< Arp >() )
    {
      Arp a = p.getApp<Arp>();
      if( a.opcode() == arpopcode::response )
      {
        MACAddress mac = MACAddress(a.senderMacAddress().vector());
        IPv4Address ip = IPv4Address(a.senderIPAddress().vector());
        cache_->addEntry( ip.toString(), mac );
        sendAlert( ip.toString() );
      }
    }
  }
}

void ArpListener::setArpFilter(const std::string &filter)
{
  arpFilter_ = filter;
}

std::string ArpListener::arpFilter() const
{
  return arpFilter_;
}

void ArpListener::setDevice(const std::string &device)
{
  device_ = device;
}

std::string ArpListener::device() const
{
  return device_;
}

void ArpListener::setAlert( const std::string &ip )
{

  //Assumes that alertMutx_ is locked
  std::map< std::string, std::pair<bool, Condition* > >::iterator itr = alerts_.lower_bound(ip);

  if( itr != alerts_.end() && !(alerts_.key_comp()(ip, itr->first) ) )
  {
    itr->second.first = true; //multiple request so we need to broadcast and not signal
    return;
  }
  else
  {
    alerts_[ip] = std::make_pair( false, new Condition );
  }
}

void ArpListener::removeAlert(const std::string &ip)
{
  //Assumes that alertMutx_ is locked

  std::map< std::string, std::pair<bool, Condition* > >::iterator itr = alerts_.lower_bound(ip);

  if( itr != alerts_.end() && !(alerts_.key_comp()(ip, itr->first) ) )
  {
    if( !itr->second.first ) //only one thread requested this
    {
      delete itr->second.second;
      alerts_.erase( ip );
    }
    //else we don't know how many threads want this so do nothing
  }
}

void ArpListener::sendAlert( const std::string &ip )
{
  MutexLocker lock( alertMutex_ );
  std::map< std::string, std::pair< bool, Condition* > >::iterator itr = alerts_.lower_bound(ip);

  if( itr != alerts_.end() && !(alerts_.key_comp()(ip, itr->first) ) )
  { //exist
    std::pair<bool, Condition* > stuff = itr->second;
    if( stuff.first )
      stuff.second->broadcast();
    else
      stuff.second->signal();
    delete stuff.second;
    alerts_.erase( ip );
  }
}

void ArpListener::waitForResponse(const std::string &ip)
{
  MutexLocker lock( alertMutex_ );
  if(!( cache_->lookup(ip) == MACAddress( std::vector< uint8_t  >( 6, 0 ) ) ) )
    return; //there is a mac in the cache
  setAlert(ip);
  std::map< std::string, std::pair< bool, Condition* > >::iterator itr = alerts_.lower_bound(ip);

  if( itr != alerts_.end() && !(alerts_.key_comp()(ip, itr->first) ) )
  { //exist
    itr->second.second->wait(alertMutex_);
  }
  removeAlert(ip);
  //else the alert either already happend or didn't exists
}

void ArpListener::waitForResponse(const std::string &ip, const timespec &timeout)
{
  MutexLocker lock( alertMutex_ );
  if(!( cache_->lookup(ip) == MACAddress( std::vector< uint8_t  >( 6, 0 ) ) ) )
    return; //there is a mac in the cache
  setAlert(ip);
  std::map< std::string, std::pair< bool, Condition* > >::iterator itr = alerts_.lower_bound(ip);

  if( itr != alerts_.end() && !(alerts_.key_comp()(ip, itr->first) ) )
  { //exist
    itr->second.second->timeWait(alertMutex_, timeout );
  }
  removeAlert(ip);
  //else the alert either already happend or didn't exists
}
