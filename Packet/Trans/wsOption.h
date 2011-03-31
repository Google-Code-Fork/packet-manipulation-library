#ifndef WS_OPTION_H
#define WS_OPTION_H 

#include "tcpOptions.h"

const uint8_t WINDOW_SCALE_LENGTH = 3; //RFC 1323
 
class WSOption : public TCPOption
{
	public:
		WSOption() 
		{ 
			kind_ = WINDOW_SCALE; 
			isSingleOctet_ = false;
			length_ = WINDOW_SCALE_LENGTH;
			data_.push_back( 0 );
		}

		WSOption(const uint8_t *bytes, int size)
		{
			kind_ = WINDOW_SCALE; 
			isSingleOctet_ = false;
			length_ = WINDOW_SCALE_LENGTH;
			if( size >= WINDOW_SCALE_LENGTH )
			{
				data_.push_back( bytes[2] );
			}
			else
			{
				data_.push_back( 0 );
			}
		}

		WSOption( const WSOption & o ):TCPOption() 
		{ 
			kind_ = WINDOW_SCALE; 
			isSingleOctet_ = false;
			length_ = WINDOW_SCALE_LENGTH;
			data_.push_back( o.data_[0] );
		}

		void setKind( const uint8_t &/*kind*/ ) {} //don't do anything
		void setLength( const uint8_t &/*length*/ ) {}
		void setData( const std::vector< uint8_t > &/*data*/ ) {}
		void singleOctet( const bool &/*isit*/ ) {}

		void setScaleFactor( const uint8_t &factor )
		{
			data_[0] = factor;
		}

};


#endif
