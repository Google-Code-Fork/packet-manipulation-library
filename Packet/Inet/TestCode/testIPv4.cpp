#include "testIPv4.h"

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

IPv4Test::IPv4Test( std::ostream &out, int verboseLevel ) : qunit(
		out, verboseLevel)
{
}

int IPv4Test::run()
{
	testIsIpv4();
	testPacketCreation();
	return qunit.errors();
}

void IPv4Test::testIsIpv4()
{
	IPv4 ipv4;
	QUNIT_IS_TRUE( ipv4.isIPv4() );
}

void IPv4Test::testPacketCreation()
{
	//20 bytes IPv4 header taken from a wireshark dump
	uint8_t bits[] = { 0x45, 0x00, 0x00, 0x30, 0x62, 0xd7, 0x40, 0x00, 0x80,
		0x06, 0xf8, 0x7b, 0xa3, 0xf0, 0xa8, 0xe7, 0xc1, 0x6e, 0x91, 0x2e };

	//construct IPv4 header from bytes above
	IPv4 ipv4_1( bits, 20 );

	//copy
	IPv4 ipv4_2( ipv4_1 );

	//isIPv4
	QUNIT_IS_TRUE( ipv4_1.isIPv4() );
	QUNIT_IS_TRUE( ipv4_2.isIPv4() );

	//size
	QUNIT_IS_EQUAL( ipv4_1.size(), ipv4_2.size() );
	QUNIT_IS_TRUE( ipv4_1.size() == 20 );

	//version
	QUNIT_IS_TRUE( ipv4_1.version() == 4);

	//setversion
	ipv4_1.setVersion(0x06);
	QUNIT_IS_TRUE( ipv4_1.version() == 6);
	ipv4_1.setVersion(0x05);
	QUNIT_IS_TRUE( ipv4_1.version() == 5);
	ipv4_1.setVersion(15);
	QUNIT_IS_TRUE( ipv4_1.version() ==15);
	//change the version back to 4
	ipv4_1.setVersion(0x04);

	//headerLength
	QUNIT_IS_TRUE( ipv4_1.headerLength() == 20 );

	//setHeaderLength
	ipv4_1.setHeaderLength(12);
	QUNIT_IS_TRUE( ipv4_1.headerLength() == 12);
	ipv4_1.setHeaderLength(24);
	QUNIT_IS_TRUE( ipv4_1.headerLength() == 24);
	//change the header length back to 20 (=5 words)
	ipv4_1.setHeaderLength(20);

	//totalLength
	QUNIT_IS_TRUE( ipv4_1.totalLength() == 48 );

	//setTotalLength
	ipv4_1.setTotalLength(0x0040);
	QUNIT_IS_TRUE( ipv4_1.totalLength() == 64 );
	//change the total length back to 48
	ipv4_1.setTotalLength(48);

	//identification
	QUNIT_IS_TRUE( ipv4_1.identification() == 0x62d7 );

	//setIdentifaction
	ipv4_1.setIdentification(0x6666);
	QUNIT_IS_TRUE( ipv4_1.identification() == 0x6666 );
	//change the identification field back to original (0x62d7)
	ipv4_1.setIdentification(0x62d7);

	//Flag - returns dontfragment flag (true|false)
	QUNIT_IS_TRUE( ipv4_1.dontFragment() );
	//set dontfragment flag
	ipv4_1.setDontFragment( false );
	QUNIT_IS_FALSE( ipv4_1.dontFragment() );
	//set dontfragment -> true
	ipv4_1.setDontFragment();
	QUNIT_IS_TRUE( ipv4_1.dontFragment() );

	//Flag - returns moreFragment flag (true|false)
			QUNIT_IS_FALSE( ipv4_1.moreFragments() );
			//set moreFragment flag to false
			ipv4_1.setMoreFragments( false );
			QUNIT_IS_FALSE( ipv4_1.moreFragments() );
			//set moreFragment flag to true
			ipv4_1.setMoreFragments();
			QUNIT_IS_TRUE( ipv4_1.moreFragments() );

			//check fragment offset field
			QUNIT_IS_TRUE( ipv4_1.fragmentOffset() == 0x0000 );
			//set fragment offset field
			ipv4_1.setFragmentOffset( 0x0006 );
			QUNIT_IS_TRUE( ipv4_1.fragmentOffset() == 0x0006 );

			//check ttl value
			QUNIT_IS_TRUE( ipv4_1.ttl() == 128 );
			//set ttl value
			ipv4_1.setTtl( 0x60 );
			QUNIT_IS_TRUE( ipv4_1.ttl() == 96 );
			// set back to 128
			ipv4_1.setTtl( 0x80 );
			
			//check protocol field
			QUNIT_IS_EQUAL( ipv4_1.protocol(), ipProtocol::TCP );
			//set protocol field
			ipv4_1.setProtocol( ipProtocol::ICMP );
			QUNIT_IS_EQUAL( ipv4_1.protocol(), ipProtocol::ICMP );
			

			//check checksum value (both are OK!)
			QUNIT_IS_TRUE( ipv4_1.checksum() == 0xf87b );
			QUNIT_IS_TRUE( ipv4_1.checksum() == 63611 );
			//set the checksum and check value
			ipv4_1.setChecksum( 0x33c3 );
			QUNIT_IS_TRUE( ipv4_1.checksum() == 13251 );

			//correct values for source & destination IP addresses
			uint8_t rightSourceAddress[] = {0xa3, 0xf0, 0xa8, 0xe7};
			uint8_t rightDesinationAddress[] = {0xc1, 0x6e, 0x91, 0x2e};
			uint32_t correctSource = 0xa3f0a8e7;
			QUNIT_IS_TRUE( ipv4_1.sourceAddress() == correctSource);
			uint32_t correctDestination = 0xc16e912e;
			QUNIT_IS_TRUE( ipv4_1.destinationAddress() == correctDestination );
		}

#ifndef GLOBAL_SCOPE
int main()
{
	return IPv4Test( std::cerr ).run();
}
#endif
