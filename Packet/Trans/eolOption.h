#ifndef EOL_OPTION
#define EOL_OPTION

#include "tcpOptions.h"

class EOLOption : public TCPOptions
{
	EOLOption() { kind_ = END_OF_LIST; isSingleOctet_ = true; }
	EOLOption( const EOLOption & o ) { kind_ = EOL_OPTION; isSingleOctet_ = true; }

	void setKind( uint8_t kind ) {} //don't do anything
	void setLength( uint8_t length ) {}
	void setData( std::vector< uint8_t > data ) {}
	void singleOctet( bool isit ) {}
	
}


#endif
