#include "packet.h"

Packet::Packet()
{
}

Packet::~Packet()
{
}

Packet::Packet( const Packet &p )
{
  linkLayer_ = p.linkLayer_;
  inetLayer_ = p.inetLayer_;
  transLayer_ = p.transLayer_;
  appLayer_ = p.appLayer_;
}

Packet& Packet::operator=( const Packet &p )
{
  linkLayer_ = p.linkLayer_;
  inetLayer_ = p.inetLayer_;
  transLayer_ = p.transLayer_;
  appLayer_ = p.appLayer_;

  return *this;
}

Packet& Packet::operator+=( const Packet &n )
{
  std::vector< LinkData >::const_iterator litr;
  std::vector< InetData >::const_iterator iitr;
  std::vector< TransData >::const_iterator titr;
  std::vector< AppData >::const_iterator aitr;
  for( litr = n.linkLayer_.begin(); litr != n.linkLayer_.end(); ++litr )
  {
    linkLayer_.push_back( *litr );
  }
  for( iitr = n.inetLayer_.begin(); iitr != n.inetLayer_.end(); ++iitr )
  {
    inetLayer_.push_back( *iitr );
  }
  for( titr = n.transLayer_.begin(); titr != n.transLayer_.end(); ++titr )
  {
    transLayer_.push_back( *titr );
  }
  for( aitr = n.appLayer_.begin(); aitr != n.appLayer_.end(); ++aitr )
  {
    appLayer_.push_back( *aitr );
  }

  return *this;
}

Packet operator+( const Packet &l, const Packet &r )
{
  Packet tmp( l );
  tmp += r;
  return tmp;
}

std::vector< uint8_t > Packet::makePacket()
{
  std::vector< uint8_t > packet;
  //TODO
  return packet;
}

void Packet::pushBackLink( LinkData l )
{
  linkLayer_.push_back( l );
}

void Packet::pushBackInet( InetData i )
{
  inetLayer_.push_back( i );
}

void Packet::pushBackApp( AppData a ) 
{
  appLayer_.push_back( a );
}

void Packet::pushBackTrans( TransData t )
{
  transLayer_.push_back( t );
}

int Packet::linkSize()
{
  return linkLayer_.size();
}

int Packet::inetSize()
{
  return inetLayer_.size();
}

int Packet::transSize()
{
  return transLayer_.size();
}

int Packet::appSize()
{
  return appLayer_.size();
}


