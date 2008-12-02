#ifndef RAW_H
#define RAW_H

#include "appData.h"
#include <vector>

class Raw : public AppData
{
  public: 
    Raw();
    Raw( const uint8_t* data, int size );
    Raw( const Raw &n );
    Raw& operator=( const Raw &n );
    virtual ~Raw();
    PacketBuffer makePacket() const;
    int getSize() const;
    void setData( std::vector< uint8_t > data );
    std::vector< uint8_t > getData() const;
    bool isRaw() const {return true;}

  private:
    std::vector<uint8_t> data_;
};

#endif
