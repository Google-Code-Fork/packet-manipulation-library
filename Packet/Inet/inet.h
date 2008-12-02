#ifndef INET_H 
#define INET_H
#include <stdexcept>
#include "inetData.h"
#include "ipv4.h"

class Inet 
{
  public:
    Inet( )
    {
      header_ = NULL;
    }

    Inet( IPv4 ip )
    {
      header_ = new IPv4( ip );
    }

    Inet( const Inet &n )
    {
      copy( n );
    }

    Inet& operator=( const Inet &n )
    {
      if( header_ )
	delete header_;
      copy( n );
      return *this;
    }
    
    virtual ~Inet() 
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

  private:
   
    void copy( const Inet &n )
    {
      if( n.header_ == NULL )
      {
	header_ = NULL;
      }
      else if( n.header_->isIPv4() )
      {
	header_ = new IPv4( *((IPv4*)n.header_) );
      }
      else
	header_ = NULL;
    }

    InetData* header_;
};

template<> bool Inet::is<IPv4>( )
{
  return header_->isIPv4();
}



#endif
