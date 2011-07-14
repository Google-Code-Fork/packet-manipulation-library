#ifndef ARPAGENT_H
#define ARPAGENT_H

#include "../Sniffer/sniffer.h"
#include "../Packet/packet.h"
#include "arpcache.h"
#include "arplistener.h"
#include "arprequestor.h"
#include <time.h>

class ArpAgent
{
public:
  explicit ArpAgent();
  virtual ~ArpAgent();

  void setArpTimeout( const uint &miliseconds );
  void setArpRetryLimit( const uint &retries );
  //Cache Settings
  void setCacheTimeout( const uint &seconds );
  void setIPv4Address( const IPv4Address& ip );
  void setIPv4Gateway( const IPv4Address& gateway );
  void setNetmask( const IPv4Address &netmask );
  void setMacAddress( const MACAddress &mac );
  void setDeviceName ( const std::string &device );

  uint cacheTimeout( ) const;
  uint arpTimeout( ) const;
  uint arpRetryLimit( ) const;
  IPv4Address ipv4Address() const;
  IPv4Address gateway() const;
  IPv4Address netmask() const;
  MACAddress macAddress() const;
  std::string device() const;
  void startAgent();
  void stopAgent();

  MACAddress arp( IPv4Address ip );

private:
  Mutex startedMutex_;
  bool started_;
  MACAddress mac_;
  IPv4Address ip_;
  IPv4Address gateway_;
  IPv4Address netmask_;
  uint arpTimeout_;
  uint arpRetryLimit_;
  ArpCache cache_;
  ArpListener listener_;
  ArpRequestor requestor_;
};

#endif // ARPAGENT_H
