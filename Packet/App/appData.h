#ifndef APPDATA_H
#define APPDATA_H

#include "../packetBuffer.h"

class AppData
{
  public:
    AppData() {}
    virtual ~AppData() {}
    virtual bool isRaw() const {return false;}
};

#endif
