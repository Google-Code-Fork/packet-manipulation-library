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


#ifndef UDP_H 
#define UDP_H

#include <string>
#include <pcap.h>
#include <netinet/in.h>
#include "transData.h"

struct my_udp {
	u_int16_t sport; //source port
	u_int16_t dport; //destination port
	u_int16_t length;
	u_int16_t checksum;
};


class UDP : public TransData
{
  public:
    static const int UDPSize = 8;

  public:
    UDP();
    UDP( const uint8_t *packet, int size );
    UDP( const UDP &n );
    UDP& operator =( const UDP &n );

    ~UDP();


    uint16_t getSourcePort();
    void setSourcePort( uint16_t );
    uint16_t getDestinationPort();
    void setDestinationPort( uint16_t );
    uint16_t getChecksum();
    void setChecksum( uint16_t );
    uint16_t getLength();
    void setLength( uint16_t );
    int getSize();
    std::vector< uint8_t > makePacket();

  private:
    struct my_udp *header_;
};




#endif 
