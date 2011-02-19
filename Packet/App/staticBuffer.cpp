#include "staticBuffer.h"
#include <iostream>

StaticBuffer::StaticBuffer(): str_(NULL), size_(0)
{
}

StaticBuffer::~StaticBuffer( )
{
	if( str_ )
	{
		delete [] str_;
	}

}

StaticBuffer::StaticBuffer( const StaticBuffer &n )
{
	str_ = new uint8_t [n.size_];
	size_ = n.size_;
	for( uint32_t i = 0; i < size_; ++i )
	{
		str_[i] = n.str_[i];
	}
}

StaticBuffer::StaticBuffer( const std::string &s ):str_(NULL), size_(0)
{
	setString( s );
}

StaticBuffer::StaticBuffer( const std::vector< uint8_t > &b ):str_(NULL), size_(0)
{
	setData( b );
}

StaticBuffer& StaticBuffer::operator=( const StaticBuffer &n )
{
	if( str_ )
	{
		delete [] str_;
	}

	str_ = new uint8_t [n.size_];
	size_ = n.size_;
	for( uint32_t i = 0; i < size_; ++i )
	{
		str_[i] = n.str_[i];
	}

	return *this;
}

std::string StaticBuffer::toSTDString( ) const
{
	return std::string( (const char*) (str_) ); //null terminated so it acts like a c_str
}

void StaticBuffer::setString( const std::string &s )
{
	if( str_ )
		delete [] str_;

	size_ = s.size();
	str_  = new uint8_t [size_ + 1]; //+1 for NULL char
	for( uint32_t i = 0; i < s.size(); ++i )
	{
		str_[i] = s[i];
	}
	str_[size_] = NULL;
}

uint64_t StaticBuffer::memorySize() const
{
	//Always try to be exact but when there is an error error on the conservative
	//side
	#ifdef __X86_64__
		const int wordsize  = 8;
  #elif defined( i386 )
		const int wordsize = 4;
	#else
		const int wordsize = 8; // guess on the larger size
	#endif
		
	uint64_t size = 0;
	//Must add extra for allocation information that the compiler stores by magic
	//for us. See:
	//http://www.parashift.com/c++-faq-lite/compiler-dependencies.html#faq-38.7
	//std::cerr << "uint32_t" << sizeof( uint32_t ) << std::endl;
	//std::cerr << "str_" << sizeof( str_ ) << std::endl;
	// size = size of size_ + size of ptr_ + size of data_ + size of size
	// allocated (as place by compiler)
	size += sizeof( uint32_t ) + sizeof( str_ ) + (sizeof( uint8_t ) * size_) + (2 * wordsize);

	//does it end on a word boundard if not add up
	if( size % wordsize != 0 )
	{
		size = (( size / wordsize ) + 1) * wordsize;
	}
	return size;
}

void StaticBuffer::setData( const std::vector< uint8_t > &b )
{
	if( str_ )
		delete [] str_;
	
	size_ = b.size(); //+1 for NULL char
	str_  = new uint8_t [size_ +1];
	for( uint32_t i = 0; i < b.size(); ++i )
	{
		str_[i] = b[i];
	}
	str_[size_] = NULL;
}

std::vector< uint8_t > StaticBuffer::toVector() const
{
	std::vector< uint8_t > vector;
	for( uint32_t i = 0; i < size_; ++i )
	{
		vector.push_back( str_[i] );
	}
	return vector;
}

uint32_t StaticBuffer::size() const
{
	return size_;
}
