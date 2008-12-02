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


#ifndef CONSTANTS_H
#define CONSTANTS_H


namespace net {
	//protocols of the ip header
	const int TCP = 6;
	const int UDP = 17;
	const int ICMP = 1;

	//ICMP TYPES
	const int EchoRequest = 8;
	const int EchoReply = 0;
	const int TimeOut = 11;
	//end ICMP
	const int IGMP = 2;
	const int OSPF = 89;
	const int SCTP = 132;
	//Ethernet Types
	const uint16_t IP = 0x0800;
	const uint16_t DOT1Q = 0x8100;
	const uint16_t ARP = 0x0806;
	
	const int Eth_Alen = 6; //Octets in one ethernet addr (not using linux
				//header file so that it compiles on mac. 
	const int SizeOfEthernetHeader = 14;
	const int SizeOfDot1Q = 4;
	const int SizeOfUDPHeader = 8;
}

namespace communication {
	const int ServerPort = 5000;
	const int RefreshTime = 2;
	const int EdgeLife = 180; //3 minutes

	//Channel Modes
	const uint8_t Config = 1;
	const uint8_t GraphRefresh = 2;
	const uint8_t NodeData = 3;
	const uint8_t FilterTypes = 4;
	const uint8_t RemovedEdges = 5;
}

namespace traceroute {
	const int workerThreads = 30;
	const int MAX_TTL = 30;
	const int TRACEROUTE_TTL = 3600; //1 hour
	const int ICMPTIMEOUT = 3; //sec
	const int IP_HEADER_SIZE = 20; //RFC 791
	const int ICMP_HEADER_SIZE = 8; //RFC 792
	const int MAX_SIZE = 65200; //Payload size of ICMP message
	const int MAX_ICMP_SIZE = MAX_SIZE + ICMP_HEADER_SIZE;
	const int MAX_REPLY_SIZE = IP_HEADER_SIZE + ICMP_HEADER_SIZE + MAX_ICMP_SIZE;
}

namespace sniff {
	const int MAX_PACKETS_QUEUED = 10000;
}

namespace inav {
extern bool DEBUG;
}
#endif
