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

		SACKPremittedOption( const EOLOption &  ):TCPOption()
		{ 
			kind_ = SACK_PERMITTED; 
			isSingleOctet_ = false; 
			length_ = 2;
		}

		void setKind( const uint8_t &/*kind*/ ) {} //don't do anything
		void setLength( const uint8_t &/*length*/ ) {}
		void setData( const std::vector< uint8_t > &/*data*/ ) {}
		void singleOctet( const bool &/*isit*/ ) {}

};


#endif
