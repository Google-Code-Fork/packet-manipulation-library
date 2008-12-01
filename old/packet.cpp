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


#include "packet.h"
#include "icmp.h"
#include "../common/constants.h"
#include <iostream>
#include <iomanip>
Packet::Packet()
{
	/* DEBUG
	 * //std::cerr << "DEBUG: Default Constructor" << std::endl;
	 */
	data_ = NULL;
	ethernet_ = NULL;
	ip_ = NULL;
	tcp_ = NULL;
	udp_ = NULL;
	icmp_ = NULL;
	dataLength_ = 0;
}

Packet::Packet( const uint8_t* packet, const int size )
{
	ethernet_ = NULL;
	ip_ = NULL;
	icmp_ = NULL;
	udp_ = NULL;
	tcp_ = NULL;
	data_ = NULL;
	captureTime_.tv_sec = 0;
	captureTime_.tv_usec = 0;
	captureLength_ = size;
	actualLength_ = size;
	ethernet_ = new Ethernet( packet );
	if ( ethernet_->getType() == net::IP || ( ethernet_->getType() == net::DOT1Q  && ethernet_->getDot1QType() == net::IP ))
	{
		ip_ = new IP( stripEthernetHeader( packet ) );
		if ( ip_->getProtocol() == net::TCP )
		{
			tcp_ = new TCP( stripIPHeader( packet ) );
		}
		else if ( ip_->getProtocol() == net::UDP )
		{
			udp_ = new UDP( stripIPHeader( packet ) );
		}
		else if ( ip_->getProtocol() == net::ICMP )
		{
			icmp_ = new ICMP( stripIPHeader( packet ), size - (net::SizeOfEthernetHeader + ip_->getHeaderLength()));
		}
		else
		{
			//some other type of packet not supported
			tcp_ = NULL;//no-op
		}
	}
	else if ( ethernet_->getType() == net::ARP )
	{
		//Process ARP Packets
		tcp_ = NULL;//no-op
	}
	else
	{
		//Some other type of packet not supported
		tcp_ = NULL;//no-op
	}
	/* DEBUG
	std::cerr << "DEBUG: Capture Length - " << captureLength_ << std::endl;
	std::cerr << "DEBUG: Actual Length - " << actualLength_ << std::endl;
	*/
	data_ = setData( packet );
}

Packet::Packet( const uint8_t* packet, const struct pcap_pkthdr* pkthdr )
{
	/* DEBUG
	 * std::cerr << "CONSTRUCTOR" << std::endl;
	 */
	ethernet_ = NULL;
	ip_ = NULL;
	icmp_ = NULL;
	tcp_ = NULL;
	udp_ = NULL;
	data_ = NULL;
	captureTime_ = pkthdr->ts;
	captureLength_ = pkthdr->caplen;
	actualLength_ = pkthdr->len;
	if( actualLength_ < 14 ) //smaller than just ethernet...
	  throw std::runtime_error("Malformed Packet");
	ethernet_ = new Ethernet( packet );
	if ( ethernet_->getType() == net::IP )
	{
		ip_ = new IP( stripEthernetHeader( packet ) );
		if ( ip_->getProtocol() == net::TCP )
		{
			tcp_ = new TCP( stripIPHeader( packet ) );
		}
		else if ( ip_->getProtocol() == net::UDP )
		{
			udp_ = new UDP( stripIPHeader( packet ) );
		}
		else if ( ip_->getProtocol() == net::ICMP )
		{
			icmp_ = new ICMP( stripIPHeader( packet ), 
					pkthdr->caplen - (net::SizeOfEthernetHeader + ip_->getHeaderLength()));
		}
		else
		{
			//some other type of packet not supported
			tcp_ = NULL;//no-op
		}
	}
	else if ( ethernet_->getType() == net::ARP )
	{
		//Process ARP Packets
		tcp_ = NULL;//no-op
	}
	else
	{
		//Some other type of packet not supported
		tcp_ = NULL;//no-op
	}
	/* DEBUG
	std::cerr << "DEBUG: Capture Length - " << captureLength_ << std::endl;
	std::cerr << "DEBUG: Actual Length - " << actualLength_ << std::endl;
	*/
	data_ = setData( packet );
}

Packet::Packet( const Packet &n )
{
	ethernet_ = NULL;
	ip_ = NULL;
	icmp_ = NULL;
	tcp_ = NULL;
	udp_ = NULL;
	data_= NULL;
	/* DEBUG
	 * std::cerr << "COPY CONSTRUCTOR" << std::endl;
	 */
	if( n.ethernet_ != NULL )
	{
		ethernet_ = new Ethernet(*(n.ethernet_ ));
	}
	if( n.ip_ != NULL )
	{
		ip_ = new IP(*(n.ip_));
	}
	if( n.udp_ != NULL )
	{
		udp_ = new UDP;
		*udp_ = *(n.udp_);
	}
	if( n.tcp_ != NULL )
	{
		tcp_ = new TCP;
		*tcp_ = *(n.tcp_);
	}
	if( n.icmp_ != NULL )
	{
		icmp_ = new ICMP( *(n.icmp_));
	}
	if( n.data_ != NULL )
	{
		data_ = new uint8_t[n.dataLength_];
		dataLength_ = n.dataLength_;
		for( int i = 0; i < dataLength_; ++i )
			data_[i] = n.data_[i];
	}
	else
	{
		dataLength_ = 0;
	}
	captureTime_ = n.captureTime_;
	captureLength_ = n.captureLength_;
	actualLength_ = n.actualLength_;
}

void Packet::startAtIPHeader( const uint8_t *packet, int size )
{
	//Remove everything
	if( ethernet_ )
		delete ethernet_;
	ethernet_ = NULL;
	if( ip_ )
		delete ip_;
	ip_ = NULL;
	if( tcp_ )
		delete tcp_;
	tcp_ = NULL;
	if( udp_ )
		delete udp_;
	udp_ = NULL;
	if( icmp_ )
		delete icmp_;
	icmp_ = NULL;
	if( data_ )
		delete [] data_;
	data_ = NULL;
	captureTime_.tv_sec = 0;
	captureTime_.tv_usec = 0;
	//set everything accordingly
	captureLength_ = size;
	actualLength_ = size;
	ip_ = new IP( packet );
	if ( ip_->getProtocol() == net::TCP )
	{
		tcp_ = new TCP( packet + ip_->getHeaderLength() ); 
	}
	else if ( ip_->getProtocol() == net::UDP )
	{
		udp_ = new UDP( packet + ip_->getHeaderLength() );//; stripIPHeader( packet ) );
	}
	else if ( ip_->getProtocol() == net::ICMP )
	{
		icmp_ = new ICMP( packet + ip_->getHeaderLength(), size - ip_->getHeaderLength() );
	}
	else
	{
		//some other type of packet not supported
		tcp_ = NULL;//no-op
	}
	int headerSize = ip_->getHeaderLength();
	if( icmp_ )
		headerSize += icmp_->getHeaderLength();
	uint8_t* data = new uint8_t[ size - headerSize ];
	for( int i = 0; i < (size - headerSize); ++i )
	{
		data[i] = packet[ headerSize + i ];
	}
	data_ = data;
	//data_ = packet + ip_->getHeaderLength() + icmp_->getHeaderLength();

}

Packet& Packet::operator =( const Packet &n )
{
	/* DEBUG
	std::cerr << "ASSIGNMENT" << std::endl;
	*/
	if( n.ethernet_ != NULL )
	{
		if( ethernet_ == NULL )
			ethernet_ = new Ethernet;
		*ethernet_ = *(n.ethernet_);
	}
	else
	{
		if( ethernet_ )
			delete ethernet_;
		ethernet_ = NULL;
	}

	if( n.ip_ != NULL )
	{
		if( ip_ == NULL )
			ip_ = new IP;
		*ip_ = *(n.ip_);
	}
	else
	{
		if( ip_ )
			delete ip_;
		ip_ = NULL;
	}

	if( n.tcp_ != NULL )
	{
		if( tcp_ == NULL )
			tcp_ = new TCP;
		*tcp_ = *(n.tcp_);
	}
	else
	{
		if( tcp_ )
			delete tcp_;
		tcp_ = NULL;
	}

	if( n.udp_ != NULL )
	{
		if( udp_ == NULL )
			udp_ = new UDP;
		*udp_ = *(n.udp_);
	}
	else
	{
		if( udp_ )
			delete udp_;
		udp_ = NULL;
	}

	if( n.icmp_ != NULL )
	{
		if( icmp_ == NULL )
			icmp_ = new ICMP;
		*icmp_ = *(n.icmp_);
	}
	else
	{
		if( icmp_ )
			delete icmp_;
		icmp_ = NULL;
	}

	if( data_ )
		delete [] data_;
	data_ = NULL;
	
	data_ = new uint8_t[n.dataLength_];
	dataLength_ = n.dataLength_;
	for( int i = 0; i < dataLength_; ++i )
		data_[i] = n.data_[i];

	captureLength_ = n.captureLength_;
	captureTime_ = n.captureTime_;
	actualLength_ = n.actualLength_;

}

Packet::~Packet()
{
	/* DEBUG
	 * std::cerr << "Deconstructor" << std::endl;
	 */
	if( data_ != NULL )
		delete [] data_;
	data_ = NULL;
	if( ethernet_ != NULL )
		delete ethernet_;
	if( ip_ != NULL )
		delete ip_;
	if( tcp_ != NULL )
		delete tcp_;
	if( icmp_ != NULL )
		delete icmp_;
	if( udp_ != NULL )
		delete udp_;
}

const uint8_t* Packet::stripEthernetHeader( const uint8_t *packet )
{
	return packet+ethernet_->getSize();
}

const uint8_t* Packet::stripIPHeader( const uint8_t *packet )
{
	const uint8_t *tmp = stripEthernetHeader( packet );
	return tmp + ip_->getHeaderLength();
}

const uint8_t* Packet::stripTCPHeader( const uint8_t *packet )
{
	const uint8_t *tmp = stripIPHeader( packet );
	return tmp + tcp_->getDataOffset();
}

const uint8_t* Packet::stripUDPHeader( const uint8_t *packet )
{
	const uint8_t *tmp = stripIPHeader( packet );
	return tmp + net::SizeOfUDPHeader;
}

uint8_t* Packet::setData( const uint8_t *packet )
{
	const uint8_t* tmp;
	int sizeOfHeader = 0;
	if( tcp_ != NULL )
	{
		sizeOfHeader = net::SizeOfEthernetHeader + ip_->getHeaderLength() + tcp_->getDataOffset();
		//std::cerr << "DEBUG: TCP" << std::endl;
		tmp = stripTCPHeader( packet );
	}
	else if ( udp_ != NULL )
	{
		tmp = stripUDPHeader( packet );
	}
	else if ( ip_ != NULL )
	{
		sizeOfHeader = net::SizeOfEthernetHeader + ip_->getHeaderLength();
		//std::cerr << "DEBUG: IP" << std::endl;
		tmp = stripIPHeader( packet );
	}
	else
	{
		sizeOfHeader = net::SizeOfEthernetHeader;
		//std::cerr << "DEBUG: Ethernet" << std::endl;
		tmp = stripEthernetHeader( packet );
	}
  dataLength_ = captureLength_ - sizeOfHeader;	
	/* DEBUG
	 * std::cerr << "Size of Data: " << dataLength_ << std::endl;
	 */
	//std::cerr << "DataLength: " << dataLength_ << std::endl;
	uint8_t* newData = new uint8_t[dataLength_];
	for( int i=0; i < dataLength_; ++i )
	{
		newData[i] = tmp[i];
	}
	return newData;
}

uint32_t Packet::getCaptureSize()
{
	return (uint32_t)captureLength_;
}

void Packet::setCaptureSize( uint32_t size )
{
	captureLength_ = size;
}

uint32_t Packet::getActualSize()
{
	return (uint32_t)actualLength_;
}

void Packet::setActualSize( uint32_t size )
{
	actualLength_ = size;
}

bool Packet::isTCP()
{
	return ( tcp_ != NULL );
}

void Packet::isTCP( bool set )
{
	if( set )
	{
		if( tcp_ == NULL )
			tcp_ = new TCP();
		if( ip_ == NULL )
			ip_ = new IP();
		ip_->setProtocol( net::TCP );
	}
	else
	{
		delete tcp_;
	}
}

bool Packet::isIP()
{
	return ( ip_ != NULL );
}

void Packet::isIP( bool set )
{
	if( set )
	{
		if( ip_ == NULL )
			ip_ = new IP();
	}
	else
	{
		if( tcp_ != NULL )
			delete tcp_;
		if( udp_ != NULL )
			delete udp_;
		if( ip_ != NULL )
			delete ip_;
	}
}

bool Packet::isICMP()
{
	return ( icmp_ != NULL );
}

void Packet::isICMP( bool set )
{
	if( set )
	{
		if( ip_ == NULL )
			ip_ = new IP();
		if( icmp_ == NULL )
			icmp_ = new ICMP();
		ip_->setProtocol( net::ICMP );
	}
	else
	{
		delete icmp_;
	}
}

bool Packet::isUDP()
{
	return ( udp_ != NULL );
}

void Packet::isUDP( bool set )
{
	if( set ) 
	{
		if( ip_ == NULL )
			ip_ = new IP();
		if( udp_ == NULL )
			udp_ = new UDP();
		ip_->setProtocol( net::UDP );
	}
	else
	{
		delete udp_;
	}
}

std::string Packet::getDestinationMAC()
{
	checkETHER();
	return ethernet_->getDestinationMAC();
}

void Packet::setDestinationMAC( std::string mac )
{
	checkETHER();
	ethernet_->setDestinationMAC( mac );
}

std::string Packet::getSourceMAC()
{
	checkETHER();
	return ethernet_->getSourceMAC();
}

void Packet::setSourceMAC( std::string mac )
{
	checkETHER();
	ethernet_->setSourceMAC( mac );
}

uint16_t Packet::getType()
{
	checkETHER();
	return ethernet_->getType();
}

void Packet::setType( uint16_t type )
{
	checkETHER();
	ethernet_->setType( type );
}

uint8_t Packet::getIPVersion()
{
	checkIP();
	return ip_->getVersion();
}

void Packet::setIPVersion( uint8_t version )
{
	checkIP();
	ip_->setVersion( version );
}

uint8_t Packet::getIPHeaderLength()
{
	checkIP();
	return ip_->getHeaderLength();
}

void Packet::setIPHeaderLength( uint8_t length )
{
	checkIP();
	ip_->setHeaderLength( length );
}

void Packet::setIPTotalLength( uint16_t length )
{
	checkIP();
	ip_->setTotalLength( length );
}

uint16_t Packet::getIPTotalLength()
{
	checkIP();
	return ip_->getTotalLength();
}

uint16_t Packet::getIPIdentification()
{
	checkIP();
	return ip_->getIdentifaction();
}

void Packet::setIPIdentification( uint16_t id )
{
	checkIP();
	ip_->setIdentifaction( id );
}

bool Packet::getIPFlagsNoFragment()
{
	checkIP();
	return ip_->getFlagsNoFragment();
}

void Packet::setIPFlagsNoFragment( bool  set )
{
	checkIP();
	ip_->setFlagsNoFragment( set );
}

bool Packet::getIPFlagsMoreFragments()
{
	checkIP();
	return ip_->getFlagsMoreFragments();
}

void Packet::setIPFlagsMoreFragments( bool set )
{
	checkIP();
	ip_->setFlagsMoreFragments( set );
}

uint16_t Packet::getIPFragmentOffset()
{
	checkIP();
	return ip_->getFragmentOffset();
}

void Packet::setIPFragmentOffset( uint16_t offset )
{
	checkIP();
	ip_->setFragmentOffset( offset );
}

uint8_t Packet::getTTL()
{
	checkIP();
	return ip_->getTTL();
}

void Packet::setTTL( uint8_t ttl )
{
	checkIP();
	ip_->setTTL( ttl );
}

uint8_t Packet::getProtocol()
{
	checkIP();
	return ip_->getProtocol();
}

void Packet::setProtocol( uint8_t protocol )
{
	checkIP();
	ip_->setProtocol( protocol );
}

uint16_t Packet::getIPChecksum()
{
	checkIP();
	return ip_->getChecksum();
}

void Packet::setIPChecksum( uint16_t checksum )
{
	checkIP();
	ip_->setChecksum( checksum );
}

uint32_t Packet::getSourceAddress()
{
	checkIP();
	return ip_->getSourceAddress();
}

void Packet::setSourceAddress( uint32_t ip )
{
	checkIP();
	ip_->setSourceAddress( ip );
}

uint32_t Packet::getDestinationAddress()
{
	checkIP();
	return ip_->getDestinationAddress();
}

void Packet::setDestinationAddress( uint32_t ip )
{
	checkIP();
	ip_->setDestinationAddress( ip );
}

void Packet::checkUDP()
{
	if( udp_ == NULL )
		throw std::runtime_error( "UDP Header Doesn't Exists" );
}

void Packet::checkIP()
{
	if( ip_ == NULL )
		throw std::runtime_error( "IP Header Doesn't Exists" );
}

void Packet::checkTCP()
{
	if( tcp_ == NULL )
		throw std::runtime_error( "TCP Header Doesn't Exists" );
}

void Packet::checkICMP()
{
	if( icmp_ == NULL )
		throw std::runtime_error( "ICMP Header Doesn't Exists" );
}

void Packet::checkETHER()
{
	if( ethernet_ == NULL )
		throw std::runtime_error( "Ethernet Header Doesn't Exists" );
}
	
uint16_t Packet::getUDPSourcePort()
{
	checkUDP();
	return udp_->getSourcePort();
}

void Packet::setUDPSourcePort( uint16_t port )
{
	checkUDP();
	udp_->setSourcePort( port );
}

uint16_t Packet::getUDPDestinationPort()
{
	checkUDP();
	return udp_->getDestinationPort();
}

void Packet::setUDPDestinationPort( uint16_t port )
{
	checkUDP();
	udp_->setDestinationPort( port );
}

uint16_t Packet::getUDPLength()
{
	checkUDP();
	return udp_->getLength();
}

void Packet::setUDPLength( uint16_t length )
{
	checkUDP();
	udp_->setLength( length );
}

uint16_t Packet::getUDPChecksum()
{
	checkUDP();
	return udp_->getChecksum();
}

void Packet::setUDPChecksum( uint16_t checksum )
{
	checkUDP();
	udp_->setChecksum( checksum );
}

uint16_t Packet::getTCPSourcePort()
{
	checkTCP();
	return tcp_->getSourcePort();
}

void Packet::setTCPSourcePort( uint16_t port )
{
	checkTCP();
	tcp_->setSourcePort( port );
}

uint16_t Packet::getTCPDestinationPort()
{
	checkTCP();
	return tcp_->getDestinationPort();
}

void Packet::setTCPDestinationPort( uint16_t port )
{
	checkTCP();
	tcp_->setDestinationPort( port );
}

uint32_t Packet::getTCPSequenceNumber()
{
	checkTCP();
	return tcp_->getSequenceNumber();
}

void Packet::setTCPSequenceNumber( uint32_t num )
{
	checkTCP();
	tcp_->setSequenceNumber( num );
}

uint32_t Packet::getTCPAcknowledgementNumber()
{
	checkTCP();
	return tcp_->getAcknowledgementNumber();
}

void Packet::setTCPAcknowledgementNumber( uint32_t ackNum )
{
	checkTCP();
	tcp_->setAcknowledgementNumber( ackNum );
}

uint8_t Packet::getTCPDataOffset()
{
	checkTCP();
	return tcp_->getDataOffset();
}

void Packet::setTCPDataOffset( uint8_t offset )
{
	checkTCP();
	tcp_->setDataOffset( offset );
}

bool Packet::getTCPFlagsCWR()
{
	checkTCP();
	return tcp_->getFlagsCWR();
}

inline void Packet::setTCPFlagsCWR()
{
	setTCPFlagsCWR( true );
}

void Packet::setTCPFlagsCWR( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsCWR( true ) : tcp_->setFlagsCWR( false );
}

bool Packet::getTCPFlagsECE()
{
	checkTCP();
	return tcp_->getFlagsECE();
}

inline void Packet::setTCPFlagsECE()
{
	setTCPFlagsECE( true );
}

void Packet::setTCPFlagsECE( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsECE( true ) : tcp_->setFlagsECE( false );
}

bool Packet::getTCPFlagsURG()
{
	checkTCP();
	return tcp_->getFlagsURG();
}

inline void Packet::setTCPFlagsURG()
{
	setTCPFlagsURG( true );
}

void Packet::setTCPFlagsURG( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsURG( true ) : tcp_->setFlagsURG( false );
}

bool Packet::getTCPFlagsACK()
{
	checkTCP();
	return tcp_->getFlagsACK();
}

inline void Packet::setTCPFlagsACK()
{
	setTCPFlagsACK( true );
}

void Packet::setTCPFlagsACK( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsACK( true ) : tcp_->setFlagsACK( false );
}

bool Packet::getTCPFlagsPSH()
{
	checkTCP();
	return tcp_->getFlagsPSH();
}

inline void Packet::setTCPFlagsPSH()
{
	setTCPFlagsPSH( true );
}

void Packet::setTCPFlagsPSH( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsPSH( true ) : tcp_->setFlagsPSH( false );
}

bool Packet::getTCPFlagsRST()
{
	checkTCP();
	return tcp_->getFlagsRST();
}

inline void Packet::setTCPFlagsRST()
{
	setTCPFlagsRST( true );
}

void Packet::setTCPFlagsRST( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsRST( true ) : tcp_->setFlagsRST( false );
}

bool Packet::getTCPFlagsSYN()
{
	checkTCP();
	return tcp_->getFlagsSYN();
}

inline void Packet::setTCPFlagsSYN()
{
	setTCPFlagsSYN( true );
}

void Packet::setTCPFlagsSYN( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsSYN( true ) : tcp_->setFlagsSYN( false );
}

bool Packet::getTCPFlagsFIN()
{
	checkTCP();
	return tcp_->getFlagsFIN();
}

inline void Packet::setTCPFlagsFIN()
{
	setTCPFlagsFIN( true );
}

void Packet::setTCPFlagsFIN( bool set )
{
	checkTCP();
	set ? tcp_->setFlagsFIN( true ) : tcp_->setFlagsFIN( false );
}


uint16_t Packet::getTCPWindow()
{
	checkTCP();
	return tcp_->getWindow();
}

void Packet::setTCPWindow( uint16_t window )
{
	checkTCP();
	tcp_->setWindow( window );
}

uint16_t Packet::getTCPChecksum()
{
	checkTCP();
	return tcp_->getChecksum();
}

void Packet::setTCPChecksum( uint16_t checksum )
{
	checkTCP();
	tcp_->setChecksum( checksum );
}

uint16_t Packet::getTCPUrgentPointer()
{
	checkTCP();
	return tcp_->getUrgentPointer();
}

void Packet::setTCPUrgentPointer( uint16_t pointer )
{
	checkTCP();
	tcp_->setUrgentPointer( pointer );
}

uint8_t Packet::getICMPType()
{
	checkICMP();
	return icmp_->getType();
}

void Packet::setICMPType( uint8_t type )
{
	checkICMP();
	icmp_->setType( type );
}

uint8_t Packet::getICMPCode()
{
	checkICMP();
	return icmp_->getCode();
}

void Packet::setICMPCode( uint8_t code )
{
	checkICMP();
	icmp_->setCode( code );
}

uint16_t Packet::getICMPChecksum()
{
	checkICMP();
	return icmp_->getChecksum();
}

void Packet::setICMPChecksum( uint16_t checksum )
{
	checkICMP();
	icmp_->setChecksum( checksum );
}

uint16_t Packet::getICMPIdentifier()
{
	checkICMP();
	return icmp_->getIdentifier();
}

void Packet::setICMPIdentifier( uint16_t id )
{
	checkICMP();
	icmp_->setIdentifier( id );
}

uint16_t Packet::getICMPSequenceNum()
{
	checkICMP();
	return icmp_->getSequenceNum();
}

void Packet::setICMPSequenceNum( uint16_t num )
{
	checkICMP();
	icmp_->setSequenceNum( num );
}

Packet Packet::getOrginalPacket()
{
	checkICMP();
	return icmp_->getOrginalPacket();
}
