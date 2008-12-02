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
  std::vector< Link >::const_iterator litr;
  std::vector< Inet >::const_iterator iitr;
  std::vector< Trans >::const_iterator titr;
  std::vector< App >::const_iterator aitr;
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

PacketBuffer Packet::makePacket() const
{
  PacketBuffer pb;
  std::vector< uint8_t > packet;
  std::vector< LinkData >::const_iterator litr;
  std::vector< InetData >::const_iterator iitr;
  std::vector< TransData >::const_iterator titr;
  std::vector< AppData >::const_iterator aitr;
  for( litr = linkLayer_.begin(); litr != linkLayer_.end(); ++litr )
  {
    pb += litr->makePacket( );
  }
  for( iitr = inetLayer_.begin(); iitr != inetLayer_.end(); ++iitr )
  {
    pb += iitr->makePacket( );
  }
  for( titr = transLayer_.begin(); titr != transLayer_.end(); ++titr )
  {
    pb += titr->makePacket( );
  }
  for( aitr = appLayer_.begin(); aitr != appLayer_.end(); ++aitr )
  {
    pb += aitr->makePacket( );
  }
  
  return pb;
}

int Packet::linkSize() const
{
  return linkLayer_.size();
}

int Packet::inetSize() const
{
  return inetLayer_.size();
}

int Packet::transSize() const
{
  return transLayer_.size();
}

int Packet::appSize() const
{
  return appLayer_.size();
}


