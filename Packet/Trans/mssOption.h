#ifndef EOL_OPTION
#define EOL_OPTION

#include "tcpOptions.h"

class MSSOption : public TCPOptions
{
	MSSOption() 
	{
		kind_ = MAXIMUM_SEGMENT_SIZE; 
		length_ = 4; 
		isSingleOctet_ = false; 
		data_.push_back(0); 
		data_.push_back(0); 
	}

	MSSOption( const MSSOption & o ) 
	{ 
		kind_ = MAXIMUM_SEGMENT_SIZE; 
		isSingleOctet_ = false; 
		length_ = 4;
		data_.push_back( o.data_[0] );
		data_.push_back( o.data_[1] );
	}

	void setKind( uint8_t kind ) {} //don't do anything
	void setLength( uint8_t length ) {}
	void setData( std::vector< uint8_t > data ) {}
	void singleOctet( bool isit ) {}
	
	void setMSS( uint16_t size )
	{
		uint16_t networkOrder = htons( size );
		data_.clear();
		data_.push_back( static_cast<uint8_t>( networkOrder >> 8 ) );
		data_.push_back( static_cast<uint8_t>( networkOrder & 0xFF ) );
	}
}


#endif
