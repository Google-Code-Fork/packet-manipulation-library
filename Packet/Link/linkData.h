#ifndef LINKDATA_H
#define LINKDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"

class LinkData : public Encapsulateable  
{
  public:
    LinkData(){ }
    virtual ~LinkData() {}
    virtual bool isEthernet() const { return false; }
    virtual bool isMac() const { return false; }
    virtual PacketBuffer makePacket() const { return PacketBuffer(); }
    virtual int getSize() const { return 0; }
};


#endif
