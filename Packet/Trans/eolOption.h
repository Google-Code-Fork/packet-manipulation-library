#ifndef EOL_OPTION_H
#define EOL_OPTION_H

#include "tcpOptions.h"

class EOLOption : public TCPOption
{
	public:
	EOLOption() { kind_ = END_OF_LIST; isSingleOctet_ = true; }
	EOLOption( const EOLOption & o ) { kind_ = END_OF_LIST; isSingleOctet_ = true; }

	void setKind( uint8_t kind ) {} //don't do anything
	void setLength( uint8_t length ) {}
	void setData( std::vector< uint8_t > data ) {}
	void singleOctet( bool isit ) {}
	
};



#endif
