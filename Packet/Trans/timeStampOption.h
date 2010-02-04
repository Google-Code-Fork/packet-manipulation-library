#ifndef TIME_STAMP_OPTION_H 
#define TIME_STAMP_OPTION_H 
#include "tcpOptions.h"

const uint8_t TIME_STAMP_SIZE = 10;

class TimeStampOption : public TCPOption
{
	public:
	TimeStampOption() 
	{ 
		kind_ = TIME_STAMP_OPTION; 
		isSingleOctet_ = false; 
		length_ = TIME_STAMP_SIZE;
	  //initialize 8 bytes worth of data	
		for( int i = 0; i < 8; ++i )
			data_.push_back( 0 );
	}
	
	TimeStampOption( const uint8_t *bytes, int size ) 
	{ 
		kind_ = TIME_STAMP_OPTION; 
		isSingleOctet_ = false; 
		length_ = TIME_STAMP_SIZE;
		for( int i = 0; i < 8; ++i )
			data_.push_back( 0 );
	  //initialize 8 bytes worth of data
		if( size >= TIME_STAMP_SIZE )
		{
			setTSVAL( *(reinterpret_cast<const uint32_t* >( bytes + 2 ) ) );
			setTSecr( *(reinterpret_cast<const uint32_t* >( bytes + 6 ) ) );
		}
	}

	TimeStampOption( const TimeStampOption & o ) 
	{
		kind_ = TIME_STAMP_OPTION;
		isSingleOctet_ = true;
		length_ = TIME_STAMP_SIZE;
		data_ = o.data_;
	}

	void setKind( uint8_t kind ) {} //don't do anything
	void setLength( uint8_t length ) {}
	void setData( std::vector< uint8_t > data ) {}
	void singleOctet( bool isit ) {}

	void setTSVAL( uint32_t value )
	{
		data_[0] = static_cast<uint8_t>( (value & 0xFF000000) >> 24 );
		data_[1] = static_cast<uint8_t>( (value & 0x00FF0000) >> 16 );
		data_[2] = static_cast<uint8_t>( (value & 0x0000FF00) >> 8 );
		data_[3] = static_cast<uint8_t>( value & 0xFF );
	}

	void setTSecr( uint32_t value )
	{
		data_[4] = static_cast<uint8_t>( (value & 0xFF000000) >> 24 );
		data_[5] = static_cast<uint8_t>( (value & 0x00FF0000) >> 16 );
		data_[6] = static_cast<uint8_t>( (value & 0x0000FF00) >> 8 );
		data_[7] = static_cast<uint8_t>( value & 0xFF );
	}

};


#endif
