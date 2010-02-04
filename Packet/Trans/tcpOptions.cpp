#include "tcpOptions.h"

TCPOption::TCPOption( ): kind_(0), length_(0), isSingleOctet_(true) 
{
}

TCPOption::TCPOption( const TCPOption &o )
{
	kind_ = o.kind_;
	length_ = o.length_;
	data_ = o.data_;
	isSingleOctet_ = o.isSingleOctet_;
}

TCPOption::~TCPOption()
{
}

void TCPOption::setKind( uint8_t kind )
{
	kind_ = kind;
}

void TCPOption::setLength( uint8_t length )
{
	length_ = length;
}

void TCPOption::setData( std::vector< uint8_t > data ) 
{
	data_ = data;
}

void TCPOption::singleOctet( bool isit )
{
	isSingleOctet_ = isit;
}

std::vector< uint8_t > TCPOption::packetData()
{
	std::vector< uint8_t > data;
	data.push_back( kind_ );
	if( !isSingleOctet_ )
	{
		data.push_back( length_ );
		std::vector< uint8_t >::iterator itr;
		for( itr = data_.begin(); itr != data_.end(); ++itr )
		{
			data.push_back( *itr );
		}
	}
	return data;
}
