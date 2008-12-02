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

PacketBuffer::PacketBuffer( const PacketBuffer& n )
{
  buff_ = new uint8_t[ n.size_ ];
  size_ = n.size_;
  for( int i = 0; i < size_; ++i )
  {
    buff_[i] = n.buff_[i];
  }
}

PacketBuffer& PacketBuffer::operator=( const PacketBuffer &n )
{
  if( buff_ )
    delete [] buff_;
  buff_ = new uint8_t[ n.size_ ];
  size_ = n.size_;
  for( int i = 0; i < size_; ++i )
  {
    buff_[i] = n.buff_[i];
  }

  return *this;
}

PacketBuffer& PacketBuffer::operator+=( const PacketBuffer &n )
{
  int newSize = size_ + n.size_;
  uint8_t* newBuff = new uint8_t[ newSize ];
  for( int i = 0; i < size_; ++i )
  {
    newBuff[i] = buff_[i];
  }
  for( int i = size_; i < size_ + n.size_; ++i )
  {
    newBuff[ i ] = n.buff_[ i - size_ ];
  }
  delete [] buff_;
  buff_ = newBuff;
  size_ = newSize;
  return *this;
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
