#ifndef LINKDATA_H
#define LINKDATA_H

#include "../packetBuffer.h"

class LinkData  
{
  public:
    LinkData(){ }
    virtual ~LinkData() {}
    virtual bool isEthernet() const { return false; }
    virtual bool isMac() const { return false; }
};


#endif
