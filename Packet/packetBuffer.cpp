#include "packetBuffer.h"

PacketBuffer::PacketBuffer()
{
  buff_ = NULL;
  size_ = 0;
}

PacketBuffer::PacketBuffer( std::vector< uint8_t > buff )
{
  size_ = buff.size();
  buff_ = new uint8_t[ size_ ];
  for( int i=0; i < size_; ++i )
  {
    buff_[i] = buff[i];
  }
}

PacketBuffer::PacketBuffer( uint8_t* buff, int size )
{
  size_ = size;
  buff_= new uint8_t[ size ];
  for( int i = 0; i < size_; ++i )
  {
    buff_[i] = buff[i];
  }
}

PacketBuffer::~PacketBuffer()
{
  if( buff_ )
    delete [] buff_;
}

void PacketBuffer::setBuffer( std::vector< uint8_t > buff )
{
  if( buff_ )
    delete [] buff_;
  size_ = buff.size();
  buff_ = new uint8_t[ size_ ];
  for( int i = 0; i < size_; ++i )
    buff_[i] = buff[i];
}

void PacketBuffer::setBuffer( uint8_t* buff, int size )
{
  if( buff_ ) 
    delete [] buff_;
  size_ = size; 
  buff_ = new uint8_t[ size_ ];
  for( int i = 0; i < size_; ++i )
    buff_[i] = buff[i];
}

uint8_t* PacketBuffer::getBuffer()
{
  return buff_;
}

int PacketBuffer::size()
{
  return size_;
}
