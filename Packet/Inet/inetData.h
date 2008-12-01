#ifndef LINKDATA_H
#define LINKDATA_H

#include "../encapsulateable.h"

class InetData : public Encapsulateable
{
  public:
    InetData();
    virtual ~InetData();
    //virtual std::vector< uint8_t > makePacket() = 0;
    //virtual int getSize() = 0;
};

#endif
