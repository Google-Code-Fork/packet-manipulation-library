#ifndef EOL_OPTION
#define EOL_OPTION

#include "tcpOptions.h"

class SACKPremittedOption : public TCPOptions
{
	SACKPremittedOption() 
	{
		kind_ = SACK_PERMITTED;
		isSingleOctet_ = false;
		length_ = 2; 
	}

	SACKPremittedOption( const EOLOption & o ) 
	{ 
		kind_ = EOL_OPTION; 
		isSingleOctet_ = false; 
		length_ = 2;
	}

	void setKind( uint8_t kind ) {} //don't do anything
	void setLength( uint8_t length ) {}
	void setData( std::vector< uint8_t > data ) {}
	void singleOctet( bool isit ) {}
	
}


#endif
