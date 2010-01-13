#ifndef EOL_OPTION
#define EOL_OPTION

#include "tcpOptions.h"

class SACKOption : public TCPOptions
{
	SACKOption() 
	{ 
		kind_ = SACK; 
		isSingleOctet_ = false; 
		length_ = 2;
	}

	SACKOption( const SACKOption & o ) 
	{ 
		kind_ = SACK; 
		isSingleOctet_ = false;
		length_ = o.length_;
		data_ = o.data_;
	}

	void setKind( uint8_t kind ) {} //don't do anything
	void setLength( uint8_t length ) {}
	void setData( std::vector< uint8_t > data ) {}
	void singleOctet( bool isit ) {}

	void clear()
	{
		length_ = 2;
		data_.clear();
	}

	void addAck( uint32_t begin, uint32_t end )
	{
		data_.push_back( static_cast< uint8_t >( (begin & 0xFF000000) >> 24 ) ); 
		data_.push_back( static_cast< uint8_t >( (begin & 0x00FF0000) >> 16 ) ); 
		data_.push_back( static_cast< uint8_t >( (begin & 0x0000FF00) >> 8 ) ); 
		data_.push_back( static_cast< uint8_t >( begin & 0x000000FF) ); 
		
		data_.push_back( static_cast< uint8_t >( (end & 0xFF000000) >> 24 ) ); 
		data_.push_back( static_cast< uint8_t >( (end & 0x00FF0000) >> 16 ) ); 
		data_.push_back( static_cast< uint8_t >( (end & 0x0000FF00) >> 8 ) ); 
		data_.push_back( static_cast< uint8_t >( end & 0x000000FF) ); 

		length_ += 8;
	}
	
}


#endif
