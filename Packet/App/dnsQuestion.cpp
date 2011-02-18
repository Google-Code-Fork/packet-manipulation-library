#include "dnsPacket.h"

DNSQuestion::DNSQuestion():dnsType_(dnstype::A), dnsClass_(dnsclass::internet)
{

}

DNSQuestion::DNSQuestion( const std::string &query, uint16_t type, uint16_t dnsClass ):queryName_( query ), dnsType_(type), dnsClass_( dnsClass )
{
}

DNSQuestion::~DNSQuestion()
{
}

DNSQuestion::DNSQuestion( const DNSQuestion &n )
{
	queryName_ = n.queryName_;
	dnsType_ = n.dnsType_;
	dnsClass_ = n.dnsClass_;
}

std::string DNSQuestion::queryName() const
{
	return queryName_;
}

void DNSQuestion::setQueryName( const std::string &query )
{
	queryName_ = query;
}

uint16_t DNSQuestion::type() const
{
	return dnsType_;
}

void DNSQuestion::setType( const uint16_t &type )
{
	dnsType_ = type;
}

uint16_t DNSQuestion::dnsClass() const
{
	return dnsClass_;
}

void DNSQuestion::setDnsClass( const uint16_t &dnsClass )
{
	dnsClass_ = dnsClass;
}
