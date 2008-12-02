#ifndef TRANSDATA_H
#define TRANSDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"

class TransData : public Encapsulateable
{
  public:
    TransData() {}
    virtual ~TransData(){}
    virtual int getSize() const { return 0; }
    virtual PacketBuffer makePacket( ) const { return PacketBuffer(); }
    virtual bool isTCP() const { return false; }
    virtual bool isUDP() const { return false; }
    virtual bool isICMP() const { return false; }
};

#endif
