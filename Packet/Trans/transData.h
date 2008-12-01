#ifndef TRANSDATA_H
#define TRANSDATA_H

#include "../encapsulateable.h"

class TransData : public Encapsulateable
{
  public:
    TransData();
    virtual ~TransData();
    template <class T>bool is() { return false; }
    //virtual std::vector< uint8_t > makePacket() = 0;
    //virtual int getSize() = 0;
};

#endif
