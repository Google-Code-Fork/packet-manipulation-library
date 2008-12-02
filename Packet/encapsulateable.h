#ifndef ENCAPSULATEABLE_H
#define ENCAPSULATEABLE_H

#include <vector>
#include "packetBuffer.h"

class Encapsulateable
{
  public:
    //Encapsulateable();
    //virtual ~Encapsulateable();
    virtual PacketBuffer makePacket() const = 0; 
    virtual int getSize() const = 0;

  private:
};


#endif
