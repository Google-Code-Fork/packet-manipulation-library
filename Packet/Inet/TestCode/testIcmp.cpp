#include "testIcmp.h"

/*
 * Type: 8 (Echo Request)
 * Code: 0
 * Checksum: 0x8c53
 * Identifier: 0x0200
 * Sequence number: 48904 (0xbf08)
 * Data: (32 bytes)
 */

IcmpTest::IcmpTest( std::ostream &out, int verboseLevel ) : qunit(
		out, verboseLevel)
{
}

int IcmpTest::run()
{
	testIsIcmp();
	testConstruction();
	return qunit.errors();
}


void IcmpTest::testIsIcmp()
{
	ICMP icmp;
	QUNIT_IS_TRUE( icmp.isICMP() );
}

void IcmpTest::testConstruction()
{
	//icmp taken from wireshark dump
	uint8_t bits[] = { 0x08, 0x00, 0x8c, 0x53, 0x02, 0x00, 0xbf, 0x08, 0x61,
		0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e,
		0x6f, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x61, 0x62, 0x63,
		0x64, 0x65, 0x66, 0x67, 0x68, 0x69 };

	//construct icmp header from bytes above
	ICMP icmpA( bits, 40 );

	//copy icmp header
	ICMP icmpB( icmpA );

	//check to see if ICMP
	QUNIT_IS_TRUE( icmpA.isICMP() );
	QUNIT_IS_TRUE( icmpB.isICMP() );
	//check size of ICMP header in bytes
	QUNIT_IS_EQUAL( icmpA.size(), icmpB.size() );
	QUNIT_IS_TRUE( icmpA.size() == 40 );

	//check ICMP type
	QUNIT_IS_TRUE( icmpA.type() == 0x08 );
	QUNIT_IS_EQUAL( icmpA.type(), icmpTypes::ICMP_ECHO_REQUEST );
	//check set ICMP type
	icmpA.setType( 0x05 );
	QUNIT_IS_TRUE( icmpA.type() == 0x05 );
	icmpA.setType( icmpTypes::ICMP_DESTINATION_UNREACHABLE );
	QUNIT_IS_EQUAL( icmpA.type(), icmpTypes::ICMP_DESTINATION_UNREACHABLE );

	//check ICMP code
	QUNIT_IS_TRUE( icmpA.code() == 0x00 );
	//check set ICMP code
	icmpA.setCode( 0x01 );
	QUNIT_IS_TRUE( icmpA.code() == 0x01 );

	//check checksum
	QUNIT_IS_TRUE( icmpA.checksum() == 0x8c53 );
	//check set checksum
	icmpA.setChecksum( 0x1122 );
	QUNIT_IS_TRUE( icmpA.checksum() == 0x1122 );

	//check header length
	QUNIT_IS_TRUE( icmpA.headerLength() == icmpB.headerLength() );
	QUNIT_IS_TRUE( icmpA.headerLength() == 40 );

	//set type to equal 8
	icmpA.setType( 0x08 );
	//check icmp identifier (request)
	QUNIT_IS_TRUE( icmpA.identifier() == 0x0200 );
	//check set icmp identifier (request)
	icmpA.setIdentifier( 0x0500 );
	QUNIT_IS_TRUE( icmpA.identifier() == 0x0500 );

	//check icmp sequence number
	QUNIT_IS_TRUE( icmpA.sequenceNum() == 0xbf08 );
	//check set sequence number
	icmpA.setSequenceNum( 0xbf11 );
	QUNIT_IS_TRUE( icmpA.sequenceNum() == 0xbf11 );

	//check generate checksum
	icmpA.generateChecksum();
}

#ifndef GLOBAL_SCOPE
int main()
{
	return IcmpTest( std::cerr ).run();
}
#endif
