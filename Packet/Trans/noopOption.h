#ifndef EOL_OPTION
#define EOL_OPTION

#include "tcpOptions.h"

class NOOPOption : public TCPOptions
{
	NOOPOption() { kind_ = NO-OPERATION; isSingleOctet_ = true; }
	NOOPOption( const NOOPOption & o ) { kind_ = NO-OPERATION; isSingleOctet_ = true; }

	void setKind( uint8_t kind ) {} //don't do anything
	void setLength( uint8_t length ) {}
	void setData( std::vector< uint8_t > data ) {}
	void singleOctet( bool isit ) {}
	
}


#endif
