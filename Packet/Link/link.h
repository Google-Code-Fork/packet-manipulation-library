#ifndef LINK_H
#define LINK_H
#include <stdexcept>
#include "../encapsulateable.h"
#include "linkData.h"
#include "ethernet.h"

class Link : public Encapsulateable
{
  public:
    Link( )
    {
      header_ = NULL;
    }

    Link( Ethernet e )
    {
      header_ = new Ethernet;
      *header_ = e;
    }

    Link( MACAddress m )
    {
      header_ = new MACAddress;
      *header_ = m;
    }

    Link( const Link &n )
    {
      copy( n );
    }

    Link& operator=( const Link &n )
    {
      if( header_ )
	delete header_;
      copy( n );
      return *this;
    }
    
    virtual ~Link() 
    {
      //if( header_ )
      delete header_;
    }

    template< class T >bool is( ){ return false; }
    
    template< class T > T get( ) 
    {
      if( !( is<T>() ) )
      {
	throw std::runtime_error("wrong type");
      }
      return T(*((T*)header_));
    }

    template< class T > void set( T e )
    {
      if( header_ )
	delete header_;
      header_ = new T;
      *header_ = e;
    }

    PacketBuffer makePacket() const
    {
      return header_->makePacket();
    }

    int getSize() const
    {
      return header_->getSize();
    }

  private:
   
    void copy( const Link &n )
    {
      if( n.header_ == NULL )
      {
	header_ = NULL;
      }
      else if( n.header_->isEthernet() )
      {
	header_ = new Ethernet( *((Ethernet*)n.header_) );
      }
      else if( n.header_->isMac() )
      {
	header_ = new MACAddress( *((MACAddress*)n.header_) );
      }
      else
	header_ = NULL;
    }

    LinkData* header_;
};

template<> bool Link::is<Ethernet>( )
{
  return header_->isEthernet();
}

#endif
