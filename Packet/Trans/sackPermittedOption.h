#ifndef SACK_PREMITTED_OPTION_H
#define SACK_PREMITTED_OPTION_H

#include "tcpOptions.h"

class SACKPremittedOption : public TCPOption
{
	public:
		SACKPremittedOption() 
		{
			kind_ = SACK_PERMITTED;
			isSingleOctet_ = false;
			length_ = 2; 
		}

		SACKPremittedOption( const EOLOption & o ) 
		{ 
			kind_ = SACK_PERMITTED; 
			isSingleOctet_ = false; 
			length_ = 2;
		}

		void setKind( uint8_t kind ) {} //don't do anything
		void setLength( uint8_t length ) {}
		void setData( std::vector< uint8_t > data ) {}
		void singleOctet( bool isit ) {}

};


#endif
