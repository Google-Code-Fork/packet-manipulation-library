#ifndef TRANSDATA_H
#define TRANSDATA_H

#include "../packetBuffer.h"

class TransData
{
  public:
    TransData() {}
    virtual ~TransData(){}
    virtual bool isTCP() const { return false; }
    virtual bool isUDP() const { return false; }
    virtual bool isICMP() const { return false; }
};

#endif
