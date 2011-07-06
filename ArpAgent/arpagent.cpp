#include "arpagent.h"

ArpAgent::ArpAgent()
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
}

void ArpAgent::setDeviceName(const std::string &device)
{
  //TODO:: needs to go to the listener and the requestor
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
}

MACAddress ArpAgent::arp(const IPv4Address &ip)
{
  //TODO: make this do stuff
  //Check cache
  //Arp Request
  //Repeat as needed
}

