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
			setTSVAL( ntohl(*(reinterpret_cast<const uint32_t* >( bytes + 2 ) )) );
			setTSecr( ntohl(*(reinterpret_cast<const uint32_t* >( bytes + 6 ) )) );
		}
	}

	TimeStampOption( const TimeStampOption & o ):TCPOption()
	{
		kind_ = TIME_STAMP_OPTION;
		isSingleOctet_ = true;
		length_ = TIME_STAMP_SIZE;
		data_ = o.data_;
	}

	void setKind( const uint8_t &/*kind*/ ) {} //don't do anything
	void setLength( const uint8_t & /*length*/ ) {}
	void setData( const std::vector< uint8_t > &/*data*/ ) {}
	void singleOctet( const bool &/*isit*/ ) {}

	void setTSVAL( const uint32_t &value )
	{
		data_[0] = static_cast<uint8_t>( (value & 0xFF000000) >> 24 );
		data_[1] = static_cast<uint8_t>( (value & 0x00FF0000) >> 16 );
		data_[2] = static_cast<uint8_t>( (value & 0x0000FF00) >> 8 );
		data_[3] = static_cast<uint8_t>( value & 0xFF );
	}

	uint32_t tsval( ) const
	{
		uint32_t value = 0;
		value |= static_cast<uint32_t>(data_[0]) << 24;
		value |= static_cast<uint32_t>(data_[1]) << 16;
		value |= static_cast<uint32_t>(data_[2]) << 8;
		value |= static_cast<uint32_t>(data_[3]);

		return (value);

	}

	void setTSecr( const uint32_t &value )
	{
		data_[4] = static_cast<uint8_t>( (value & 0xFF000000) >> 24 );
		data_[5] = static_cast<uint8_t>( (value & 0x00FF0000) >> 16 );
		data_[6] = static_cast<uint8_t>( (value & 0x0000FF00) >> 8 );
		data_[7] = static_cast<uint8_t>( value & 0xFF );
	}

	uint32_t tsecr() const 
	{
		uint32_t value = 0;
		value |= static_cast<uint32_t>(data_[4]) << 24;
		value |= static_cast<uint32_t>(data_[5]) << 16;
		value |= static_cast<uint32_t>(data_[6]) << 8;
		value |= static_cast<uint32_t>(data_[7]);

		return (value);
	}
};


#endif
