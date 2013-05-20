#ifndef SACK_OPTION_H
#define SACK_OPTION_H

#include "tcpOptions.h"

class SACKOption : public TCPOption
{
	public:

		SACKOption() 
		{ 
			kind_ = SACK; 
			isSingleOctet_ = false; 
			length_ = 2;
		}

		SACKOption( const uint8_t *bytes, int size ) 
		{
			if( size > 2 )
			{
				kind_ = SACK; 
				isSingleOctet_ = false; 
				length_ = bytes[1];
			}
			else
			{
				kind_ = SACK;
				isSingleOctet_ = false; 
				length_ = 2;
				return;
			}

            if( size >= length_ )
            {
              for( int i = 2; i < length_; ++i )
                data_.push_back( bytes[i] );
            }
			else //if I can't figure out the sacks then put none
			{
				length_ = 2;
			}
		}

		SACKOption( const SACKOption & o ):TCPOption()
		{ 
			kind_ = SACK; 
			isSingleOctet_ = false;
			length_ = o.length_;
			data_ = o.data_;
		}

		void setKind( const uint8_t &/*kind*/ ) {} //don't do anything
		void setLength( const uint8_t &/*length*/ ) {}
		void setData( const std::vector< uint8_t > &/*data*/ ) {}
		void singleOctet( const bool &/*isit*/ ) {}

		void clear()
		{
			length_ = 2;
			data_.clear();
		}

		void addAck( const uint32_t &begin, const uint32_t &end )
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

};


#endif
