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


#ifndef IP_H 
#define IP_H

#include <string>
#include <pcap.h>
#include <netinet/in.h>
#include "inetData.h"
/* Structure of an internet header, naked of options.
 *
 * Taken from tcpdump source (thanks tcpdump people).
 */

typedef struct IPv4Header
{
	u_int8_t  ip_vhl;   /* header length, version */
	#define IP_V(ip)  (((ip)->ip_vhl & 0xf0) >> 4)
	#define IP_HL(ip) ((ip)->ip_vhl & 0x0f)
	u_int8_t  ip_tos;   /* type of service */
	u_int16_t ip_len;   /* total length */
	u_int16_t ip_id;    /* identification */
	u_int16_t ip_off;   /* fragment offset field */
	#define IP_DF 0x4000      /* dont fragment flag */
	#define IP_MF 0x2000      /* more fragments flag */
	#define IP_OFFMASK 0x1fff   /* mask for fragmenting bits */
	u_int8_t  ip_ttl;   /* time to live */
	u_int8_t  ip_p;   /* protocol */
	u_int16_t ip_sum;   /* checksum */
	struct  in_addr ip_src,ip_dst;  /* source and dest address */
}IPv4Header;


class IPv4 : public InetData
{
	public:
		IPv4();
		IPv4( const uint8_t *packet );
		IPv4( const IPv4 &n);
		IPv4& operator =( const IPv4 &n );
		~IPv4();

		uint8_t getVersion();
		void setVersion( uint8_t );
		uint8_t getHeaderLength();
		void setHeaderLength( uint8_t );
		uint16_t getTotalLength();
		void setTotalLength( uint16_t );
		uint16_t getIdentifaction();
		void setIdentifaction( uint16_t );
		bool getFlagsNoFragment();
		void setFlagsNoFragment( bool );
		void setFlagsNoFragment( ); // == setFlagsNoFragment( true );
		bool getFlagsMoreFragments();
		void setFlagsMoreFragments( bool );
		void setFlagsMoreFragments( ); // == setFlagsMoreFragments( true );
		uint16_t getFragmentOffset();
		void setFragmentOffset( uint16_t );
		uint8_t getTTL();
		void setTTL( uint8_t );
		uint8_t getProtocol();
		void setProtocol( uint8_t ); 
		uint16_t getChecksum();
		void setChecksum( uint16_t );
		uint32_t getSourceAddress();
		void setSourceAddress( uint32_t );
		uint32_t getDestinationAddress();
		void setDestinationAddress( uint32_t );
		std::vector< uint8_t > makePacket();
		int getSize();

	private:
		IPv4Header *header_;
};




#endif 
