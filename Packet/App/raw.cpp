#include "raw.h"

Raw::Raw()
{
}

Raw::Raw( const uint8_t* data, int size )
{
  for( int i = 0; i < size; ++i )
  {
    data_.push_back( data[i] );
  }
}

Raw::Raw( const Raw &n )
{
  data_ = n.data_;
}

Raw& Raw::operator=( const Raw &n )
{
  data_ = n.data_;
  return *this;
}

Raw::~Raw()
{
}

PacketBuffer Raw::makePacket() const
{
  return PacketBuffer( data_ );
}

int Raw::getSize() const
{
  return data_.size();
}

void Raw::setData( std::vector< uint8_t > data )
{
  data_ = data;
}

std::vector< uint8_t > Raw::getData() const
{
  return data_;
}
