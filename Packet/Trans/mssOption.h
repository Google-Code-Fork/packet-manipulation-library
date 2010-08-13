#ifndef MSS_OPTION_H
#define MSS_OPTION_H 

#include "tcpOptions.h"

class MSSOption : public TCPOption
{
	public:
		MSSOption() 
		{
			kind_ = MAXIMUM_SEGMENT_SIZE; 
			length_ = 4; 
			isSingleOctet_ = false; 
			data_.push_back(0); 
			data_.push_back(0); 
		}

		MSSOption( const uint8_t *bytes, int size )
		{
			kind_ = MAXIMUM_SEGMENT_SIZE;
			length_ = 4;
			isSingleOctet_ = false;
			if( size >= 4 )
			{
				data_.push_back( bytes[2] );
				data_.push_back( bytes[3] );
			}
			else
			{
				data_.push_back( 0 );
				data_.push_back( 0 );
			}
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

		uint16_t mss( ) const 
		{
			uint16_t networkOrder = static_cast<uint16_t>(data_[0]) << 8;
			networkOrder |= static_cast<uint16_t>(data_[1]);
			return ntohs(networkOrder);
		}

};



#endif
