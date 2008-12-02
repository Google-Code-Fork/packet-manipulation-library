#ifndef INETDATA_H
#define INETDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"
#include <iostream>

class InetData : public Encapsulateable
{
  public:
    InetData() {}
    virtual ~InetData() {}
    virtual bool isIPv4() const { return false; }
    virtual bool isIPv6() const { return false; }
    virtual int getSize() const { return 0; }
    virtual PacketBuffer makePacket() const { return PacketBuffer(); }
};

#endif
