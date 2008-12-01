#ifndef LINKDATA_H
#define LINKDATA_H

#include "../encapsulateable.h"

class TransData : public Encapsulateable
{
  public:
    TransData();
    virtual ~TransData();
    //virtual std::vector< uint8_t > makePacket() = 0;
    //virtual int getSize() = 0;
};

#endif
