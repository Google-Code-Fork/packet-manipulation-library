#ifndef PACKETBUFFER_H
#define PACKETBUFFER_H

#include <vector>

class PacketBuffer 
{
  public:
  PacketBuffer();
  PacketBuffer( std::vector< uint8_t > );
  PacketBuffer( const uint8_t* buff, int size );
  ~PacketBuffer();
  PacketBuffer( const PacketBuffer& n );
  PacketBuffer& operator=( const PacketBuffer &n );
  PacketBuffer& operator+=( const PacketBuffer &n );
  void setBuffer( std::vector< uint8_t > buff );
  void setBuffer( uint8_t* buff, int size );
  uint8_t* getBuffer();
  int size();

  private:
    uint8_t* buff_;
    int size_;
};

#endif
