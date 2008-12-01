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


#ifndef ETHERNET_H
#define ETHERNET_H

#include <string>
#include "mac.h"

typedef struct VlanTag 
{
  uint16_t vlan;
  #define vlanPriority( vlanTag ) (((vlanTag)->vlan & 0x0007 ))
  #define vlanCFI( vlanTag ) (((vlanTag)->vlan & 0x0008 ) >> 3 )
  #define vlanID( vlanTag ) (((vlanTag)->vlan & 0xFFF0 ) >> 4 )
  uint16_t type;
}VlanTag;

typedef struct EthernetHeader 
{
  uint8_t destination[MACAddress::MACAddressSize];
  uint8_t source[MACAddress::MACAddressSize];
  uint16_t protocol; //see below
}EthernetHeader;

namespace ethernetProtocol
{
  //taken from linux/if_ether.h
  const uint16_t ETH_P_LOOP = 0x0060; //Ethernet Loopback packet
  const uint16_t ETH_P_PUP = 0x0200; //Xerox PUP packet
  const uint16_t ETH_P_PUPAT = 0x0201; //Xerox PUP Addr Trans packet
  const uint16_t ETH_P_IP = 0x0800; //Internet Protocol packet
  const uint16_t ETH_P_X25 = 0x0805; //CCITT X.25		
  const uint16_t ETH_P_ARP = 0x0806; //Address Resolution packet
  const uint16_t ETH_P_BPQ = 0x08FF; //G8BPQ AX.25 Ethernet Packet	[ NOT AN OFFICIALLY REGISTERED ID ]
  const uint16_t ETH_P_IEEEPUP = 0x0a00; //Xerox IEEE802.3 PUP packet
  const uint16_t ETH_P_IEEEPUPAT = 0x0a01; //Xerox IEEE802.3 PUP Addr Trans packet
  const uint16_t ETH_P_DEC = 0x6000; // DEC Assigned proto          
  const uint16_t ETH_P_DNA_DL = 0x6001; // DEC DNA Dump/Load           
  const uint16_t ETH_P_DNA_RC = 0x6002; // DEC DNA Remote Console      
  const uint16_t ETH_P_DNA_RT = 0x6003; // DEC DNA Routing             
  const uint16_t ETH_P_LAT = 0x6004; // DEC LAT                     
  const uint16_t ETH_P_DIAG = 0x6005; // DEC Diagnostics             
  const uint16_t ETH_P_CUST = 0x6006; // DEC Customer use            
  const uint16_t ETH_P_SCA = 0x6007; // DEC Systems Comms Arch      
  const uint16_t ETH_P_RARP = 0x8035; //Reverse Addr Res packet
  const uint16_t ETH_P_ATALK = 0x809B; //Appletalk DDP	
  const uint16_t ETH_P_AARP = 0x80F3; //Appletalk AARP	
  const uint16_t ETH_P_8021Q = 0x8100; //802.1Q VLAN Extended Header 
  const uint16_t ETH_P_IPX = 0x8137; //IPX over DIX		
  const uint16_t ETH_P_IPV6 = 0x86DD; //IPv6 over bluebook	
  const uint16_t ETH_P_PAUSE = 0x8808; //IEEE Pause frames. See 802.3 31B
  const uint16_t ETH_P_SLOW = 0x8809; //Slow Protocol. See 802.3ad 43B
  const uint16_t ETH_P_WCCP = 0x883E; //Web-cache coordination proto defined in draft-wilson-wrec-wccp-v2-00.txt */
  const uint16_t ETH_P_PPP_DISC = 0x8863; //PPPoE discovery messages    
  const uint16_t ETH_P_PPP_SES = 0x8864; //PPPoE session messages
  const uint16_t ETH_P_MPLS_UC = 0x8847; //MPLS Unicast traffic	
  const uint16_t ETH_P_MPLS_MC = 0x8848; //MPLS Multicast traffic
  const uint16_t ETH_P_ATMMPOA = 0x884c; //MultiProtocol Over ATM
  const uint16_t ETH_P_ATMFATE = 0x8884; //Frame-based ATM Transp over Ethernet 
  const uint16_t ETH_P_AOE = 0x88A2; //ATA over Ethernet	
  const uint16_t ETH_P_TIPC = 0x88CA; //TIPC 		
}

class Ethernet : public LinkData
{
  public: //constants
  static const int EthernetSize = 14;
  static const int Dot1QSize = 4;

  public:
    Ethernet();
    Ethernet( const uint8_t* buff, int size );
    Ethernet( const std::vector< uint8_t > data );
    Ethernet( const Ethernet& n );
    Ethernet& operator =( const Ethernet &n);
    ~Ethernet();

    MACAddress getDestinationMAC();
    void setDestinationMAC( MACAddress mac );
    MACAddress getSourceMAC();
    void setSourceMAC( MACAddress );
    uint16_t getType();
    void setType( uint16_t );
    uint16_t getDot1QType();
    void setDot1QType( uint16_t );
    std::vector<uint8_t> makePacket();
    int getSize();

  private:
    EthernetHeader header_;
    VlanTag vlanTag_;
};

template <> bool Ethernet::LinkData::is<Ethernet>() { return true; }


#endif 
