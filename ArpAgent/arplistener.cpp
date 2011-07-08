#include "arplistener.h"

const std::string ArpListener::k_arp_filter = "arp";

void* run_listener(void *data)
{
  ArpListener *listener = reinterpret_cast< ArpListener* >(data);
  listener->listenerThread();
  return NULL;
}

ArpListener::ArpListener():running_(false), arpFilter_( k_arp_filter )
{
}

ArpListener::~ArpListener()
{
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

void ArpListener::setAlert(const std::string &ip, Condition *condition, Mutex *mutex)
{
  MutexLocker lock( alertMutex_ );
  std::map< std::string, std::pair< Condition*, Mutex*> >::iterator itr = alerts_.lower_bound(ip);

  if( itr != alerts_.end() && !(alerts_.key_comp()(ip, itr->first) ) )
  { //exist
    return;
  }


  alerts_[ip] = std::make_pair( condition, mutex );
}

void ArpListener::removeAlert(const std::string &ip)
{
  MutexLocker lock( alertMutex_ );
  alerts_.erase( ip );
}

void ArpListener::sendAlert( const std::string &ip )
{
  MutexLocker lock( alertMutex_ );
  std::map< std::string, std::pair< Condition*, Mutex*> >::iterator itr = alerts_.lower_bound(ip);

  if( itr != alerts_.end() && !(alerts_.key_comp()(ip, itr->first) ) )
  { //exist
    std::pair< Condition*, Mutex* > stuff = itr->second;
    stuff.second->lock();
    stuff.first->signal();
    stuff.second->unlock();
  }
}
