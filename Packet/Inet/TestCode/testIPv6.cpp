#include "testIPv6.h"

//IPv6 packet used for test:
//version - 6
//Traffic Class - 0
//Flow Label - 0
//Payload Length - 24 (0x0018)
//Next Header - 6 (0x06)
//Hop Limit - 64 (0x40)
//Source IP - 0x20010480154001680224e8fffea454ea
//Dest IP - 0x20014860800f00000000000000000068

IPv6Test::IPv6Test( std::ostream &out, int verboseLevel ) : qunit(
		out, verboseLevel)
{
}

int IPv6Test::run()
{
//	testIsIpv6();
	testPacketCreation();
	return qunit.errors();
}

//void IPv6Test::testIsIpv6()
//{
//	IPv6 ipv6;
//	QUNIT_IS_TRUE( ipv6.isIPv6() );
//}

void IPv6Test::testPacketCreation()
{
	//40 bytes IPv6 header taken from a wireshark dump
	uint8_t bits[] = { 0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x06, 0x40, 0x20, 0x01,
		0x04, 0x80, 0x15, 0x40, 0x01, 0x68, 0x02, 0x24, 0xe8, 0xff, 0xfe, 0xa4,
		0x54, 0xea, 0x20, 0x01, 0x48, 0x60, 0x80, 0x0f, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x68 };

	//construct IPv6 header from bytes above
	IPv6 ipv6( bits, 40 );

	QUNIT_IS_TRUE( ipv6.version() == 6 );
	
	
}


#ifndef GLOBAL_SCOPE
int main()
{
	return IPv6Test( std::cerr ).run();
}
#endif
