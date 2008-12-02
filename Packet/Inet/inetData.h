#ifndef INETDATA_H
#define INETDATA_H

#include "../packetBuffer.h"

class InetData
{
  public:
    InetData() {}
    virtual ~InetData() {}
    virtual bool isIPv4() const { return false; }
    virtual bool isIPv6() const { return false; }
};

#endif
