#include "packetBuffer.h"
#include <iostream>
PacketBuffer::PacketBuffer()
{
  buff_ = NULL;
  size_ = 0;
}

PacketBuffer::PacketBuffer( std::vector< uint8_t > buff )
{
  size_ = buff.size();
  if( size_ == 0 )
  {
    buff_ = NULL;
  }
  else
  {
    buff_ = new uint8_t[ size_ ];
    for( int i=0; i < size_; ++i )
    {
      buff_[i] = buff[i];
    }
  }
}

PacketBuffer::PacketBuffer( const uint8_t* buff, int size )
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
  size_ = n.size_;
  if( n.size_ > 0 )
  {
    buff_ = new uint8_t[ n.size_ ];
    for( int i = 0; i < size_; ++i )
    {
      buff_[i] = n.buff_[i];
    }
  }
  else
  {
    buff_ = NULL;
  }
}

PacketBuffer& PacketBuffer::operator=( const PacketBuffer &n )
{
  if( buff_ )
    delete [] buff_;
  if( n.size_ > 0 )
  {
    buff_ = new uint8_t[ n.size_ ];
    size_ = n.size_;
    for( int i = 0; i < size_; ++i )
    {
      buff_[i] = n.buff_[i];
    }
  }
  else
  {
    size_ = 0;
    buff_ = NULL;
  }

  return *this;
}

PacketBuffer& PacketBuffer::operator+=( const PacketBuffer &n )
{
  int newSize = size_ + n.size_;
  std::cerr << "newSize: " << newSize << std::endl;
  std::cerr << "size: " << size_ << std::endl;
  std::cerr << "n.size_: " << n.size_ << std::endl;
  uint8_t* newBuff = new uint8_t[ newSize ];
  for( int i = 0; i < size_; ++i )
  {
    newBuff[i] = buff_[i];
  }
  for( int i = size_; i < size_ + n.size_; ++i )
  {
    newBuff[ i ] = n.buff_[ i - size_ ];
  }
  if( buff_ )
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
  if( size_ > 0 ) 
  {
    buff_ = new uint8_t[ size_ ];
    for( int i = 0; i < size_; ++i )
      buff_[i] = buff[i];
  }
  else
  {
    buff_ = NULL;
  }
}

uint8_t* PacketBuffer::getBuffer()
{
  return buff_;
}

int PacketBuffer::size()
{
  return size_;
}
