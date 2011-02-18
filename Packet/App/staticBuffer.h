#ifndef STATIC_BUFFER_H
#define STATIC_BUFFER_H
#include <string>
#include <vector>
#include <stdint.h>

/*! \class StaticBuffer
 * This is class is for creating strings for the DNSRecords. This was needed
 * over classes like std::string because we needed to control the size and we
 * needed to improve efficiency of memory useage. This class will not allocate
 * any more space than it needs and will also allow users to query the exact
 * amount of memory is being used by the object which will allow the cache to
 * know the exact amount of memory in use and if the cache to remove its older
 * entries. 
 */

class StaticBuffer
{
	public:

		StaticBuffer();
		virtual ~StaticBuffer();
		StaticBuffer( const StaticBuffer &n );
		StaticBuffer( const std::string &s );
		StaticBuffer( const std::vector< uint8_t > &b );

		std::string toSTDString( ) const; 
		std::vector< uint8_t > toVector( ) const;
		void setString( const std::string &s );
		void setData( const std::vector< uint8_t > &data );
		uint64_t memorySize() const;
		uint32_t size() const;

	private:
		uint8_t* str_;
		uint32_t size_;
};

#endif
