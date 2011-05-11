#include "dnsPacket.h"

DNSRecord::DNSRecord():dnsType_( dnstype::A ), dnsClass_( dnsclass::internet ),timeToLive_( 0 )
{
}

DNSRecord::~DNSRecord()
{
}

DNSRecord::DNSRecord( const DNSRecord &n ): domainName_( n.domainName_ ), dnsType_( n.dnsType_ ), dnsClass_( n.dnsClass_ ), timeToLive_( n.timeToLive_ ), data_( n.data_ )
{
	
}

DNSRecord& DNSRecord::operator=( const DNSRecord &n )
{
	domainName_ = n.domainName_;
	dnsType_ = n.dnsType_;
	dnsClass_ = n.dnsClass_;
	timeToLive_ = n.timeToLive_;
	data_ = n.data_;

  return *this;
}

std::string DNSRecord::domainName( ) const 
{
	return domainName_.toSTDString();
}

void DNSRecord::setDomainName( const std::string &domainName )
{
	domainName_ = domainName;
}

uint16_t DNSRecord::type( ) const
{
	return dnsType_;
}

void DNSRecord::setType( const uint16_t &type )
{
	dnsType_ = type;
}

uint16_t DNSRecord::dnsClass( ) const
{
	return dnsClass_;
}

void DNSRecord::setDnsClass( const uint16_t &dnsClass )
{
	dnsClass_ = dnsClass;
}

uint32_t DNSRecord::timeToLive( ) const
{
	return timeToLive_;
}

void DNSRecord::setTimeToLive( const uint32_t &ttl )
{
	timeToLive_  = ttl;
}

uint16_t DNSRecord::dataLength( ) const
{
	return static_cast< uint16_t >( data_.size() );
}

std::vector< uint8_t > DNSRecord::data() const 
{
	return data_.toVector();
}

void DNSRecord::setData( const std::vector< uint8_t > &data )
{
	data_ = data;
}
/*
void DNSRecord::pushDataBack( const uint8_t &data )
{
	data_.push_back( data );
}

void DNSRecord::clearData()
{
	data_.clear();
}
*/

uint64_t DNSRecord::memorySize() const
{
	uint64_t size = 0;
	size += sizeof( dnsType_ );
	size += sizeof( dnsClass_ );
	size += sizeof( timeToLive_ );
	size += domainName_.memorySize(); 
	size += data_.memorySize();
	return size;
}




