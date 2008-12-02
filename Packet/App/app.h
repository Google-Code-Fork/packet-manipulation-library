#ifndef APP_H 
#define APP_H
#include <stdexcept>
#include "appData.h"
#include "raw.h"

class App 
{
  public:
    App( )
    {
      header_ = NULL;
    }

    App( Raw p )
    {
      header_ = new Raw( p );
    }

    App( const App &n )
    {
      copy( n );
    }

    App& operator=( const App &n )
    {
      if( header_ )
	delete header_;
      copy( n );
      return *this;
    }
    
    virtual ~App() 
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
   
    void copy( const App &n )
    {
      if( n.header_ == NULL )
      {
	header_ = NULL;
      }
      else if( n.header_->isRaw() )
      {
	header_ = new Raw( *((Raw*)n.header_) );
      }
      else
	header_ = NULL;
    }

    AppData* header_;
};

template<> bool App::is<Raw>( )
{
  return header_->isRaw();
}



#endif
