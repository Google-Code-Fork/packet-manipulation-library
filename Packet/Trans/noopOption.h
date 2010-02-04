#ifndef NOOP_OPTION_H
#define NOOP_OPTION_H

#include "tcpOptions.h"

class NOOPOption : public TCPOption
{
	public:
		NOOPOption() { kind_ = NO_OPERATION; isSingleOctet_ = true; }
		NOOPOption( const NOOPOption & o ) { kind_ = NO_OPERATION; isSingleOctet_ = true; }

		void setKind( uint8_t kind ) {} //don't do anything
		void setLength( uint8_t length ) {}
		void setData( std::vector< uint8_t > data ) {}
		void singleOctet( bool isit ) {}

};


#endif
