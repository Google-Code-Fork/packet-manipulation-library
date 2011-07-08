#ifndef ARPREQUESTOR_H
#define ARPREQUESTOR_H

#include "../Packet/packet.h"
#include <string>
#include "../Injector/injector.h"
#include "../common/threads.h"

class ArpRequestor
{
public:
  explicit ArpRequestor();
  virtual ~ArpRequestor();

  void setDevice( const std::string device );
  std::string device() const;
  void setSourceMAC( const MACAddress &mac );
  MACAddress sourceMac( ) const;
  void setSourceIP( const IPv4Address &ip );
  IPv4Address sourceIP () const;
  void arp( const IPv4Address &dest );

private:
  mutable Mutex injectorMutex_;
  Injector injector_;
  MACAddress mac_;
  IPv4Address ip_;
};

#endif // ARPREQUESTOR_H
