/*
 * PacMan - Packet Manipulation Library 
 * Copyright © 2011  Jeff Scaparra
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


#ifndef ARP_H 
#define ARP_H

#include <string>
#include <vector>
#include <deque>
#include <map>
#include <stdint.h>
#include "../packetBuffer.h"
#include "appData.h"

typedef struct my_arp {
	uint16_t hardwareType;
	uint16_t protocolType;
	uint8_t hardwareSize;
	uint8_t protocolSize;
	uint16_t opcode;
} ARPHeader;

namespace arpopcode
{
	const uint16_t reserved = 0; //RFC 5494
  const uint16_t request = 1; //RFC 826, RFC 5227
  const uint16_t response = 2; //RFC 826, RFC 5277
	const uint16_t requestReserve = 3; //RFC 903
	const uint16_t replyReserve = 4; //RFC 903
	const uint16_t DRARP_Request = 5; //RFC 1931
	const uint16_t DRARP_Reply = 6; //RFC 1931
	const uint16_t DRARP_ERROR = 7; //RFC 1931
	const uint16_t inARP_request = 8; //RFC 1293
	const uint16_t inArp_reply = 9; //RFC 1293
	const uint16_t ARP_NAK = 10; //RFC 1577
	const uint16_t MARS_Request = 11; //Grenville_Armitage
	const uint16_t MARS_Multi = 12; //Grenville_Armitage
	const uint16_t MARS_MServ = 13; //Grenville_Armitage
	const uint16_t MARS_Join = 14; //Grenville_Armitage
	const uint16_t MARS_Leave = 15; //Grenville_Armitage
	const uint16_t MARS_NAK = 16; //Grenville_Armitage
	const uint16_t MARS_Unserv = 17; //Grenville_Armitage
	const uint16_t MARS_SJoin = 18; //Grenville_Armitage
	const uint16_t MARS_SLeave = 19; //Grenville_Armitage
	const uint16_t MARS_Grouplist_Request = 20; //Grenville_Armitage
	const uint16_t MARS_Grouplist_Reply = 21; //Grenville_Armitage
	const uint16_t MARS_Redirect_Map = 22; //Grenville_Armitage
	const uint16_t MAPOS_UNARP = 23; //Mitsuru_Maruyama RFC 2176
	const uint16_t OP_EXP1 = 24; //RFC5494
	const uint16_t OP_EXP2 = 25; //RFC5494
}

namespace protocoltype
{ //RFC 5342
	const uint16_t IP = 0x0800; //Internet Protocol Version 4 (IPv4)
  const uint16_t ARP = 0x0806; //  Address Resolution Protocol (ARP)
  const uint16_t FrameRelayARP = 0x0808; //Frame Relay Arp
  const uint16_t PPTP = 0x880B; // Point-to-Point Tunneling Protocol 
  const uint16_t GSMP = 0x880C; // General Switch Management Protocol (GSMP)
  const uint16_t RARP = 0x8035; // Reverse Address Resolution Protocol (RARP)
  const uint16_t IPv6 = 0x86DD; // Internet Protocol Version 6 (IPv6)
  const uint16_t MPLS = 0x8847; // MPLS
	const uint16_t MPLS_upstream_assigned_label = 0x8848; //MPLE with upstream-assigned label
	const uint16_t MCAP = 0x8861; //Multicast Channel Allocation Procotol (MCAP)
	const uint16_t PPPoE_Discovery = 0x8863; //PPP over Ethernet (PPPoE) Discover Stage
	const uint16_t PPPoE_Session = 0x8864; //PPP over Ethernet (PPPoE) Session Stage
	const uint16_t vlan = 0x8100; // IEEE Std 802.1Q Customer VLAN Tag Type
	const uint16_t EPON = 0x8808; //Ethernet Passive Optical Network (EPON)
	const uint16_t IEEE802_1X = 0x888E; //Port-based network access control
	const uint16_t IEEE802_1Q = 0x88A8; //IEEE std 802.1Q Service VLAN tag
	const uint16_t IEEE802_EXP1 = 0x88B5; //Local Experimental Ethertype
	const uint16_t IEEE802_EXP2 = 0x88B6; //Local Experimental Ethertype
	const uint16_t IEEE802_OUI = 0x88B7; //OUI Extended Ethertype
	const uint16_t IEEE802_11i = 0x88C7; //PreAuthentication
	const uint16_t LLDP = 0x88CC; // 802.1AB - Link Layer Discovery Protocol (LLDP)
	const uint16_t MACS = 0x88E5; // Media Access Control Security
	const uint16_t MVRP = 0x88F5; //Mulltiple VLAN Registration Protocol (MVRP)
	const uint16_t MMRP = 0x88F6; //Multiple Multicast Registration Protocol (MMRP)
	const uint16_t FRRR = 0x898D; //Fast Roaming Remote Request
}

namespace hardwaretype
{
	/*
	 http://www.iana.org/assignments/arp-parameters/arp-parameters.xml
	 */

	const uint16_t RESERVED = 0x0000; 
	const uint16_t ETHERNET = 0x0001; //Ethernet (10Mb + )
	const uint16_t EXPERIMENTAL_ETHERNET = 0x0002;
	const uint16_t AMATEUR_RADIO = 0x0003; // Amateur Radio AX.25
	const uint16_t TOKEN_RELAY = 0x0004; //Proteon ProNET Token Ring
	const uint16_t CHAOS = 0x0005;
	const uint16_t IEEE802 = 0x0006; //IEEE 802 Networks
	const uint16_t ARCNET = 0x0007; //RFC1201
	const uint16_t HYPERCHANNEL = 8; 
	const uint16_t LANSTAR = 9; 
	const uint16_t AUTONET_SHORT_ADDRESS = 10;
	const uint16_t LOCALTALK = 11;
	const uint16_t LOCALNET = 12; //LOCALNET (IBM PCNet or SYTEK LocalNET)
	const uint16_t ULTRALINK = 13;
	const uint16_t SMDS = 14;
	const uint16_t FRAMERELAY = 15;
	const uint16_t ATM_1 = 16;
	const uint16_t HDLC = 17;
	const uint16_t FIBRE_CHANNEL = 18;
	const uint16_t ATM_2 = 19;
	const uint16_t SERIAL_LINE = 20;
	const uint16_t ATM_3 = 21;
	const uint16_t MIL_STD_188_220 = 22;
	const uint16_t METRICOM = 23;
	const uint16_t IEEE1394 = 24;
	const uint16_t MAPOS = 25;
	const uint16_t TWINAXIAL = 26;
	const uint16_t EUI_64 = 27;
	const uint16_t HIPARP = 28;
	const uint16_t ISO7816_3 = 29; //IP and ARP over ISOP 7816-3
	const uint16_t ARPSec = 30;
	const uint16_t IPsecTunnel = 31; //RFC 3456
	const uint16_t InfiniBand = 32; //RFC 4391
	const uint16_t CAI = 33; //TIA-102 Project 25 Common Air Interface (CAI)
	const uint16_t WIEGAND = 34; //Wiegand Interface
	const uint16_t PURE_IP = 35;
	const uint16_t HW_EXP1 = 36; //RFC 5494
	const uint16_t HFI = 37;
	//... 38-255 Unassigned
	const uint16_t HW_EXP2 = 256; //RFC 5394
}

namespace protocolsize
{
	const uint8_t IP = 4;
	const uint8_t IPv6 = 16; 
}

namespace hardwaresize
{
	const uint8_t ETHERNET = 6;
}

class Arp : public AppData
{
  public:
    Arp( );
		Arp( const uint8_t *data, int size );
    Arp( const std::vector<uint8_t> packet );
    Arp( const Arp &n );
    Arp& operator=( const Arp &n );
		Arp( const PacketBuffer &packet );
    virtual ~Arp( );

		uint16_t hardwareType() const;
		void setHardwareType( const uint16_t &hardwareType );
		uint16_t protocolType() const;
		void setProtocolType( const uint16_t &protocolType );
		uint8_t hardwareSize() const;
		void setHardwareSize( const uint8_t &size );
		uint8_t protocolSize() const;
		void setProtocolSize( const uint8_t &size );
		uint16_t opcode() const; 
		void setOpcode( const uint16_t &opcode );
		PacketBuffer senderMacAddress() const;
		void setSenderMacAddress( const PacketBuffer &pb );
		PacketBuffer senderIPAddress() const;
		void setSenderIPAddress( const PacketBuffer &pb );
		PacketBuffer targetMacAddress() const;
		void setTargetMacAddress( const PacketBuffer &pb );
		PacketBuffer targetIPAddress( ) const;
		void setTargetIPAddress( const PacketBuffer &pb );

		std::vector< uint8_t > data() const;
		PacketBuffer makePacket() const;

		bool isArp() const { return true; }


	private:
		void init( const std::vector< uint8_t > &datav );
  private:
    ARPHeader header_;
		PacketBuffer senderMacAddress_;
		PacketBuffer senderIPAddress_;
		PacketBuffer targetMacAddress_;
		PacketBuffer targetIPAddress_;
};

#endif
