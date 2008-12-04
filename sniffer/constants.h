
#ifndef CONSTANTS_H
#define CONSTANTS_H


/*namespace net {
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
}*/

namespace sniff {
	const int MAX_PACKETS_QUEUED = 10000;
}

#endif
