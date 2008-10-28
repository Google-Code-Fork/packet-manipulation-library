/**
 * * INAV - Interactive Network Active-traffic Visualization
 * * Copyright © 2007  Nathan Robinson, Jeff Scaparra
 * *
 * * This file is a part of INAV.
 * *
 * * This program is free software: you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation, either version 3 of the License, or
 * * (at your option) any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * */


#include <stdexcept>
#include "ethernet.h"
#include "../common/constants.h"
#ifdef linux
#include <netinet/ether.h>
#endif
#include <netinet/in.h>

Ethernet::Ethernet()
{
	header_ = new struct ether_header;
	vlanTag_ = NULL;
}

Ethernet::Ethernet( const uint8_t *packet )
{
	header_ = new struct ether_header;
	*header_ = *((struct ether_header *)packet);
	if( getType() == net::DOT1Q )
	{
		vlanTag_ = new struct vlanTag;
		*vlanTag_ = *((struct vlanTag* ) (packet + net::SizeOfEthernetHeader ));
	}
	else
		vlanTag_ = NULL;
}

Ethernet::Ethernet( const Ethernet& n )
{
	header_ = new struct ether_header;
	*header_ = *(n.header_);
	if( n.vlanTag_ )
	{
		vlanTag_ = new struct vlanTag;
		*vlanTag_ = *(n.vlanTag_);
	}
	else
		vlanTag_ = NULL;
}

Ethernet& Ethernet::operator =( const Ethernet &n )
{
	*header_ = *(n.header_);
	if( n.vlanTag_ )
	{
		vlanTag_ = new struct vlanTag;
		*vlanTag_ = *(n.vlanTag_);
	}
	else
		vlanTag_ = NULL;
}

Ethernet::~Ethernet()
{
	delete header_;
	if( vlanTag_ )
		delete vlanTag_;
}

std::string Ethernet::getDestinationMAC()
{
	return ether_ntoa((struct ether_addr*) header_->ether_dhost);
}

void Ethernet::setDestinationMAC( std::string MAC )
{
	struct ether_addr* mac = ether_aton( MAC.c_str() );
	if( mac == NULL )
	{
		throw std::runtime_error( "MAC Address not in correct format" );
	}
	for( int i = 0; i < net::Eth_Alen; ++i )
	{
#ifdef BSD
		header_->ether_dhost[i] = (*mac).octet[i];
#else
		header_->ether_dhost[i] = (*mac).ether_addr_octet[i];
#endif
	}
}

std::string Ethernet::getSourceMAC()
{
	return ether_ntoa((struct ether_addr*) header_->ether_shost);
}

void Ethernet::setSourceMAC( std::string MAC )
{
	struct ether_addr* mac = ether_aton( MAC.c_str() );
	if( mac == NULL )
	{
		throw std::runtime_error( "MAC Address not in correct format" );
	}
	for( int i = 0; i < net::Eth_Alen; ++i )
	{
#ifdef BSD
		header_->ether_shost[i] = (*mac).octet[i];
#else
		header_->ether_shost[i] = (*mac).ether_addr_octet[i];
#endif
	}
}
	

uint16_t Ethernet::getType()
{
	return ntohs(header_->ether_type);
}

void Ethernet::setType( uint16_t type )
{
	header_->ether_type = htons( type );
}

uint16_t Ethernet::getDot1QType( )
{
	if ( vlanTag_ != NULL )
		return vlanTag_->type;
	throw std::runtime_error( "Not Dot1Q" );
}

void Ethernet::setDot1QType( uint16_t type )
{
	if( vlanTag_ == NULL )
	{
		vlanTag_ = new struct vlanTag;
	}
	vlanTag_->type = type;
}

int Ethernet::getSize()
{
	int size = net::SizeOfEthernetHeader;
	if( vlanTag_ != NULL )
		size += net::SizeOfDot1Q;
	return size;
}

