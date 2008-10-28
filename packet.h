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


#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <pcap.h>
//for timeval stuff
#include <time.h>
#include <unistd.h>

#include "ethernet.h"
#include "ip.h"
#include "tcp.h"
//#include "icmp.h"
#include "udp.h"

class ICMP;

class Packet 
{
	public:
		Packet();
		Packet( const uint8_t* packet, const int size ); //if -1 packet starts with ip header
		Packet( const uint8_t* packet, const struct pcap_pkthdr* pkthdr );
		Packet( const Packet &n );
		void startAtIPHeader( const uint8_t *packet, const int size ); //packet buffer doesn't have ethernet data
		Packet& operator =( const Packet &n );
		~Packet();
		bool isTCP(); 
		void isTCP( bool ); //this will set the ip_->protocol to tcp it won't delete a udp structure if one exist. It will create an ip header if one does not exists.
		bool isUDP();
		void isUDP( bool );//True - This will create a udp header in an ip packet(including creation of the ip headers if needed) and set ip_->protocol to udp. False - It will remove the udp header.
		bool isICMP();
		void isICMP( bool );//True - This will create a icmp header in a ip headerif needed and set ip_->protocol to icmp. When false it removes the icmp header from the packet structure. 
		bool isIP();
		void isIP( bool ); //This will create an ip header if one doesn't exist. when passed false it will remove all upper layer headers.
		//ethernet get
		std::string getDestinationMAC();
		void setDestinationMAC( std::string MAC );
		std::string getSourceMAC();
		void setSourceMAC( std::string MAC );
		uint16_t getType();
		void setType( uint16_t type );
		uint32_t getCaptureSize();
		void setCaptureSize( uint32_t );
		uint32_t getActualSize();
		void setActualSize( uint32_t );

		//IP
		uint8_t getIPVersion();
		void setIPVersion( uint8_t );
		uint8_t getIPHeaderLength();
		void setIPHeaderLength( uint8_t );
		uint16_t getIPTotalLength();
		void setIPTotalLength( uint16_t );
		uint16_t getIPIdentification();
		void setIPIdentification( uint16_t );
		bool getIPFlagsNoFragment();
		void setIPFlagsNoFragment( bool );
		bool getIPFlagsMoreFragments();
		void setIPFlagsMoreFragments( bool );
		uint16_t getIPFragmentOffset();
		void setIPFragmentOffset( uint16_t );
		uint8_t getTTL();
		void setTTL( uint8_t );
		uint8_t getProtocol();
		void setProtocol( uint8_t );
		uint16_t getIPChecksum();
		void setIPChecksum( uint16_t );
		uint32_t getSourceAddress();
		void setSourceAddress( uint32_t );
		uint32_t getDestinationAddress();
		void setDestinationAddress( uint32_t );

		//TCP
		uint16_t getTCPSourcePort();
		void setTCPSourcePort( uint16_t );
		uint16_t getTCPDestinationPort();
		void setTCPDestinationPort( uint16_t );
		uint32_t getTCPSequenceNumber();
		void setTCPSequenceNumber( uint32_t );
		uint32_t getTCPAcknowledgementNumber();
		void setTCPAcknowledgementNumber( uint32_t );
		uint8_t getTCPDataOffset();
		void setTCPDataOffset( uint8_t );
		bool getTCPFlagsCWR();
		void setTCPFlagsCWR( );
		void setTCPFlagsCWR( bool );
		bool getTCPFlagsECE();
		void setTCPFlagsECE( );
		void setTCPFlagsECE( bool );
		bool getTCPFlagsURG();
		void setTCPFlagsURG( );
		void setTCPFlagsURG( bool );
		bool getTCPFlagsACK();
		void setTCPFlagsACK( );
		void setTCPFlagsACK( bool );
		bool getTCPFlagsPSH();
		void setTCPFlagsPSH( );
		void setTCPFlagsPSH( bool );
		bool getTCPFlagsRST();
		void setTCPFlagsRST( );
		void setTCPFlagsRST( bool );
		bool getTCPFlagsSYN();
		void setTCPFlagsSYN( );
		void setTCPFlagsSYN( bool );
		bool getTCPFlagsFIN();
		void setTCPFlagsFIN( );
		void setTCPFlagsFIN( bool );
		uint16_t getTCPWindow();
		void setTCPWindow( uint16_t );
		uint16_t getTCPChecksum();
		void setTCPChecksum( uint16_t );
		uint16_t getTCPUrgentPointer();
		void setTCPUrgentPointer( uint16_t );

		//UDP
		uint16_t getUDPSourcePort();
		void setUDPSourcePort( uint16_t );
		uint16_t getUDPDestinationPort();
		void setUDPDestinationPort( uint16_t );
		uint16_t getUDPLength();
		void setUDPLength( uint16_t );
		uint16_t getUDPChecksum();
		void setUDPChecksum( uint16_t );
		
		//ICMP
		uint8_t getICMPType();
		void setICMPType( uint8_t );
		uint8_t getICMPCode();
		void setICMPCode( uint8_t );
		uint16_t getICMPChecksum();
		void setICMPChecksum( uint16_t );
		//ICMP PING PONG
		uint16_t getICMPIdentifier();
		void setICMPIdentifier( uint16_t );
		uint16_t getICMPSequenceNum();
		void setICMPSequenceNum( uint16_t );
		//ICMP TIME TO LIVE EXCEEDED
		Packet getOrginalPacket();
		void setOrginalPacket( Packet );

	private:
		void checkUDP();
		void checkIP();
		void checkETHER();
		void checkTCP();
		void checkICMP();
		const uint8_t* stripEthernetHeader( const uint8_t *packet );
		const uint8_t* stripIPHeader( const uint8_t *packet );
		const uint8_t* stripTCPHeader( const uint8_t *packet );
		const uint8_t* stripUDPHeader( const uint8_t *packet );
		uint8_t* setData( const uint8_t *packet );

		//Member Variables
		Ethernet *ethernet_;
		IP *ip_;
		TCP *tcp_;
		UDP *udp_;
		ICMP *icmp_;
		//UDP *udp_; //add later
		u_char* data_;
		int dataLength_;
		struct timeval captureTime_;
		int captureLength_; //bytes that are available from capture
		int actualLength_; //actual bytes in the packet

};

#endif
