#ifndef ENCAPSULATEABLE_H
#define ENCAPSULATEABLE_H

#include <vector>

class Encapsulateable
{
  public:
    Encapsulateable();
    virtual ~Encapsulateable();
    virtual std::vector< uint8_t > makePacket(); 
    virtual int getSize();

  private:
};


#endif
