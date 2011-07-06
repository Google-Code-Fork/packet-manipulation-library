#include "arplistener.h"

const std::string ArpListener::k_arp_filter = "ether protocol arp";

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
