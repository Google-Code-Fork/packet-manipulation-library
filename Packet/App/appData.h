#ifndef LINKDATA_H
#define LINKDATA_H

#include "../encapsulateable.h"

class AppData : public Encapsulateable
{
  public:
    AppData();
    virtual ~AppData();
    //virtual std::vector< uint8_t > makePacket() = 0;
    //virtual int getSize() = 0;
};

#endif
