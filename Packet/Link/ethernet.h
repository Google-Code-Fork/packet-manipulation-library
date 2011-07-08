/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2008  Jeff Scaparra, Gaurav Yadav, Andrie Tanusetiawan
 *
 * This file is a part of PacMan.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/** \file ethernet.h
 * This is the declaration for the class for handling ethernet frames 
 */

/** \class Ethernet
 * This class is used in conjunction with Packet for handling Ethernet frames.
 *
 */

#ifndef ETHERNET_H
#define ETHERNET_H

#include <string>
#include "mac.h"
#include "stdint.h"

typedef struct VlanTag 
{
  /*************************************************************************
   * This is the struct used internaly by the Ethernet class to handle Vlan
   * Tagging
   ************************************************************************/
  uint16_t vlan;
  #define vlanPriority( vlanTag ) (((vlanTag)->vlan & 0x0007 ))
  #define vlanCFI( vlanTag ) (((vlanTag)->vlan & 0x0008 ) >> 3 )
  #define vlanID( vlanTag ) (((vlanTag)->vlan & 0xFFF0 ) >> 4 )
  uint16_t type;
}VlanTag;

typedef struct EthernetHeader 
{
  /*************************************************************************
   * This is the struct used internaly by the Ethernet class to handle 
   * normal Ethernet headers
   ************************************************************************/
  uint8_t destination[MACAddress::MACAddressSize]; //!< 6 Byte Destination MacAddress
  uint8_t source[MACAddress::MACAddressSize]; //!< 6 Byte Source MacAddress
  uint16_t protocol; //!< One of the protocols defined in the namespace ethernetProtocol
}EthernetHeader;

namespace ethernetProtocol
{
  //taken from linux/if_ether.h
  const uint16_t k_loop = 0x0060; //!<Ethernet Loopback packet
  const uint16_t k_pup = 0x0200; //!<Xerox PUP packet
  const uint16_t k_pupat = 0x0201; //!<Xerox PUP Addr Trans packet
  const uint16_t k_ip = 0x0800; //!<Internet Protocol packet
  const uint16_t k_x25 = 0x0805; //!<CCITT X.25
  const uint16_t k_arp = 0x0806; //!<Address Resolution packet
  const uint16_t k_bpq = 0x08FF; //!<G8BPQ AX.25 Ethernet Packet	[ NOT AN OFFICIALLY REGISTERED ID ]
  const uint16_t k_ieeepup = 0x0a00; //!<Xerox IEEE802.3 PUP packet
  const uint16_t k_ieeepupat = 0x0a01; //!<Xerox IEEE802.3 PUP Addr Trans packet
  const uint16_t k_dec = 0x6000; //!< DEC Assigned proto
  const uint16_t k_dna_dl = 0x6001; //!< DEC DNA Dump/Load
  const uint16_t k_dna_rc = 0x6002; //!< DEC DNA Remote Console
  const uint16_t k_dna_rt = 0x6003; //!< DEC DNA Routing
  const uint16_t k_lat = 0x6004; //!< DEC LAT
  const uint16_t k_diag = 0x6005; //!< DEC Diagnostics
  const uint16_t k_cust = 0x6006; //!< DEC Customer use
  const uint16_t k_sca = 0x6007; //!< DEC Systems Comms Arch
  const uint16_t k_rarp = 0x8035; //!<Reverse Addr Res packet
  const uint16_t k_atalk = 0x809B; //!<Appletalk DDP
  const uint16_t k_aarp = 0x80F3; //!<Appletalk AARP
  const uint16_t k_8021q = 0x8100; //!<802.1Q VLAN Extended Header
  const uint16_t k_ipx = 0x8137; //!<IPX over DIX
  const uint16_t k_ipv6 = 0x86DD; //!<IPv6 over bluebook
  const uint16_t k_pause = 0x8808; //!<IEEE Pause frames. See 802.3 31B
  const uint16_t k_slow = 0x8809; //!<Slow Protocol. See 802.3ad 43B
  const uint16_t k_wccp = 0x883E; //!<Web-cache coordination proto defined in draft-wilson-wrec-wccp-v2-00.txt */
  const uint16_t k_ppp_disc = 0x8863; //!<PPPoE discovery messages
  const uint16_t k_ppp_ses = 0x8864; //!<PPPoE session messages
  const uint16_t k_mpls_uc = 0x8847; //!<MPLS Unicast traffic
  const uint16_t k_mpls_mc = 0x8848; //!<MPLS Multicast traffic
  const uint16_t k_atmmpoa = 0x884c; //!<MultiProtocol Over ATM
  const uint16_t k_atmfate = 0x8884; //!<Frame-based ATM Transp over Ethernet
  const uint16_t k_aoe = 0x88A2; //!<ATA over Ethernet
  const uint16_t k_tipc = 0x88CA; //!<TIPC
}


class Ethernet : public LinkData
{
  public: //constants
  static const int EthernetSize = 14; //!<Size of an Ethernet header
  static const int Dot1QSize = 4; //!< Additional size of a Dot1Q Frame

  public: 
    //! Default Constructor for the Ethernet Class
    Ethernet();
    //! Builds an Ethernet header from a byte buffer
    Ethernet( const uint8_t* buff, int size ); 
    //! Builds an Ethernet header from a vector of bytes
    Ethernet( const std::vector< uint8_t > &data ); 
    //! Ethernets copy constructor
    Ethernet( const Ethernet& n );
    //! Ethernets equality operator
    Ethernet& operator =( const Ethernet &n);
    //! Destructor
    ~Ethernet();

    //!Returns the Destination MAC address in the Ethernet header.
    MACAddress destinationMAC();
    //!Sets the Destination Mac address in the Ethernet header to mac.
    void setDestinationMAC( MACAddress mac );
    //!Returns the Source MAC address in the Ethernet header.
    MACAddress sourceMAC();
    //!Sets the Destination Mac address in the Ethernet header to mac.
    void setSourceMAC( MACAddress );
    //!Returns the protocol of data above the Ethernet header.
    //!Protocols are defined in the namespace ethernetProtocol.
    uint16_t type();
    //!Sets the protocol of the data above the Ethernet header.
    //!If this is a dot1q frame it returns ETH_P_8021Q and getDot1QType
    //!returns the higher level protocol.
    //!Protocols are defined in the namespace ethernetProtocol.
    void setType( uint16_t );
    //!Returns the protocol of the data above the Ethernet and Dot1q addition.
    //!If this isn't a dot1q frame this function throws runtime_error.
    uint16_t dot1QType();
    //!Sets the protocol of the data above the Ethernet and Dot1q addition.
    //!If this isn't a dot1q frame this function turns it into one.
    void setDot1QType( uint16_t );
    //!This function makes a packetbuffer suitable for use with other
    //libraries.
    PacketBuffer makePacket() const;
    //!Returns the size of the Ethernet header in bytes.
    int size() const;
    //!Returns true because this is ethernet.
    //!Overloaded from LinkData.
    bool isEthernet() const;

  private:
    //!Internal data for Ethernet
    EthernetHeader header_;
    //!Internal data for Ethernet
    VlanTag vlanTag_;
};


#endif 
