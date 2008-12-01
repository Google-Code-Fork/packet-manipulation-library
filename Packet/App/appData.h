#ifndef APPDATA_H
#define APPDATA_H

#include "../encapsulateable.h"

class AppData : public Encapsulateable
{
  public:
    AppData();
    virtual ~AppData();
    template <class T>bool is() { return false; }
    //virtual std::vector< uint8_t > makePacket() = 0;
    //virtual int getSize() = 0;
};

#endif
