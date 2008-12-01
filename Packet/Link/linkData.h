#ifndef LINKDATA_H
#define LINKDATA_H

#include "../encapsulateable.h"

class LinkData : public Encapsulateable
{
  public:
    LinkData();
    virtual ~LinkData();
    //virtual std::vector< uint8_t > makePacket() = 0;
    //virtual int getSize() = 0;
};

#endif
