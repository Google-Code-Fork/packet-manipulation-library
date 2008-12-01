#ifndef INETDATA_H
#define INETDATA_H

#include "../encapsulateable.h"

class InetData : public Encapsulateable
{
  public:
    InetData() {}
    virtual ~InetData();
    template <class T>bool is() { return false; }
    //virtual std::vector< uint8_t > makePacket() = 0;
    //virtual int getSize() = 0;
};

#endif
