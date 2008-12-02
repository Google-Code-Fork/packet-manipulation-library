#ifndef APPDATA_H
#define APPDATA_H

#include "../packetBuffer.h"
#include "../encapsulateable.h"

class AppData : public Encapsulateable
{
  public:
    AppData() {}
    virtual ~AppData() {}
    virtual int getSize() const { return 0; }
    virtual PacketBuffer makePacket() const { return PacketBuffer(); }
    virtual bool isRaw() const {return false;}
    virtual bool isPacket() const { return false; }
};

#endif
