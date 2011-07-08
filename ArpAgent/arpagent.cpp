#include "arpagent.h"

ArpAgent::ArpAgent():started_(false)
{
}

ArpAgent::~ArpAgent()
{
}

void ArpAgent::setArpTimeout(const uint &miliseconds)
{
  arpTimeout_ = miliseconds;
}

void ArpAgent::setArpRetryLimit(const uint &retries)
{
  arpRetryLimit_ = retries;
}

void ArpAgent::setCacheTimeout(const uint &seconds)
{
  cache_.setTimeout(seconds);
}

void ArpAgent::setIPv4Address(const IPv4Address &ip)
{
  ip_ = ip;
  requestor_.setSourceIP( ip_ );
}

void ArpAgent::setIPv4Gateway(const IPv4Address &gateway)
{
  gateway_ = gateway;
}

void ArpAgent::setNetmask(const IPv4Address &netmask)
{
  netmask_ = netmask;
}

void ArpAgent::setMacAddress(const MACAddress &mac)
{
  mac_ = mac;
  requestor_.setSourceMAC( mac_ );
}

void ArpAgent::setDeviceName(const std::string &device)
{
  // needs to go to the listener and the requestor
  listener_.setDevice( device );
  requestor_.setDevice( device );
}

uint ArpAgent::cacheTimeout() const
{
  return cache_.timeout();
}

uint ArpAgent::arpTimeout() const
{
  return arpTimeout_;
}

uint ArpAgent::arpRetryLimit() const
{
  return arpRetryLimit_;
}

IPv4Address ArpAgent::ipv4Address() const
{
  return ip_;
}

IPv4Address ArpAgent::gateway() const
{
  return gateway_;
}

IPv4Address ArpAgent::netmask() const
{
  return netmask_;
}

MACAddress ArpAgent::macAddress() const
{
  return mac_;
}

std::string ArpAgent::device() const
{
  //TODO: grad from listener or requestor
  return listener_.device();
}

MACAddress ArpAgent::arp(const IPv4Address &ip)
{
  MutexLocker lock( startedMutex_ );
  if( !started_ )
    throw std::runtime_error( "ArpAgent not started" );
  lock.unlock();

  if( !listener_.isRunning() )
    listener_.start();


  timespec sleepTime;
  sleepTime.tv_sec = 0;
  sleepTime.tv_nsec = arpTimeout_;
  uint tries = 0;
  MACAddress mac = cache_.lookup( ip.toString() );
  Mutex responseMutex;
  Condition responseCondition;
  while( mac == MACAddress( std::vector< uint8_t >( 6, 0x00 ) ) && tries < arpRetryLimit_ )
  {
    tries++;
    responseMutex.lock();
    listener_.setAlert( ip.toString(), &responseCondition, &responseMutex );

    requestor_.arp( ip );

    bool timedout = responseCondition.timeWait( responseMutex, sleepTime ); //keep us from waiting if there was a response
    listener_.removeAlert( ip.toString() );
    responseMutex.unlock();
    if( !timedout )
    mac = cache_.lookup( ip.toString() );

  }

  return mac;
}

void ArpAgent::startAgent()
{
  MutexLocker lock( startedMutex_ );
  listener_.start();
  started_ = true;
}

void ArpAgent::stopAgent()
{
  MutexLocker lock( startedMutex_ );
  listener_.stop();
  started_ = false;
}
