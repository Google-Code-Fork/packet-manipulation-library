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
    std::vector< uint8_t > makePacket();
    int getSize();
    void setData( std::vector< uint8_t > data );
    std::vector< uint8_t > getData();

  private:
    std::vector<uint8_t> data_;
};

#endif
