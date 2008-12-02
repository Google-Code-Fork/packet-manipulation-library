#ifndef TRANS_H
#define TRANS_H
#include <stdexcept>
#include "transData.h"
#include "tcp.h"
#include "udp.h"
#include "../encapsulateable.h"

class Trans : public Encapsulateable
{
  public:
    Trans( )
    {
      header_ = NULL;
    }

    Trans( TCP tcp )
    {
      header_ = new TCP( tcp );
    }
    
    Trans( UDP udp )
    {
      header_ = new UDP( udp );
    }

    Trans( const Trans &n )
    {
      copy( n );
    }

    Trans& operator=( const Trans &n )
    {
      if( header_ )
	delete header_;
      copy( n );
      return *this;
    }
    
    virtual ~Trans() 
    {
      if( header_ )
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

    int getSize() const 
    {
      return header_->getSize();
    }

    PacketBuffer makePacket() const 
    {
      return header_->makePacket();
    }


  private:
   
    void copy( const Trans &n )
    {
      if( n.header_ == NULL )
      {
	header_ = NULL;
      }
      else if( n.header_->isTCP() )
      {
	header_ = new TCP( *((TCP*)n.header_) );
      }
      else if( n.header_->isUDP() )
      {
	header_ = new UDP( *((UDP*)n.header_) );
      }
      else
	header_ = NULL;
    }

    TransData* header_;
};

template<> bool Trans::is<UDP>( );

template<> bool Trans::is<TCP>( );



#endif
