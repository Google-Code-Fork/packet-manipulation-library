#include "../../../Test/QUnit.hpp"
#include "../ipv4.h"
#include <iostream>
#include <netinet/in.h>

//IPv4 packet used for test:
//version - 4
//header length - 20 bytes (= 5 words)
//Type of Service - 0x00
//Total Length - 48 bytes
//Identification - 0x62D7
//Flags - Don't Fragment = true; Reserved = false; more = false
//Fragment Offset - 0
//TTL - 128
//Protocol - TCP 0x06
//Checksum - 0xF87B
//Source IP - 0xA3F0A8E7 (163.240.168.231)
//Dest IP - 0xC16E912E (193.110.145.46)

class IPv4Test
{
	public:
		IPv4Test( std::ostream &out, int verboseLevel = QUnit::verbose );
		
		int run();

	private:
		QUnit::UnitTest qunit;

		void testIsIpv4();

		void testPacketCreation();
};


