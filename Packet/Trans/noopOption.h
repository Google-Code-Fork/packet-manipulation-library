#ifndef NOOP_OPTION_H
#define NOOP_OPTION_H

#include "tcpOptions.h"

class NOOPOption : public TCPOption
{
	public:
		NOOPOption() 
		{
			kind_ = NO_OPERATION; 
			isSingleOctet_ = true;
		  length_ = 1;
		}

		NOOPOption( const NOOPOption & ):TCPOption()
		{ 
			kind_ = NO_OPERATION; 
			isSingleOctet_ = true; 
			length_ = 1;
		}

		void setKind( const uint8_t &/*kind*/ ) {} //don't do anything
		void setLength( const uint8_t &/*length*/ ) {}
		void setData( const std::vector< uint8_t > &/*data*/ ) {}
		void singleOctet( const bool &/*isit*/ ) {}

};


#endif
