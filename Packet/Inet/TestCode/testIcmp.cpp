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
	uint8_t bits[] = { 0x08, 0x00, 0x8c, 0x53, 0x02, 0x00, 0xbf, 0x08 }; 

	//construct icmp header from bytes above
	ICMP icmpA( bits, 8 );

	//copy icmp header
	ICMP icmpB( icmpA );

	//check to see if ICMP
	QUNIT_IS_TRUE( icmpA.isICMP() );
	QUNIT_IS_TRUE( icmpB.isICMP() );
	//check size of ICMP header in bytes
	QUNIT_IS_EQUAL( icmpA.size(), icmpB.size() );
	QUNIT_IS_EQUAL( icmpA.size(),  8 );

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
	icmpA.setType( icmpTypes::ICMP_ECHO_REQUEST ); //so that a and b are same size
	QUNIT_IS_EQUAL( icmpA.headerLength(), icmpB.headerLength() );
	QUNIT_IS_EQUAL( icmpA.headerLength(), 8 );

	
	//check icmp identifier (request)
	//using b because it has orginal value
	QUNIT_IS_EQUAL( icmpB.identifier(),  0x0200 ); 
	//check set icmp identifier (request)
	icmpA.setIdentifier( 0x0500 );
	QUNIT_IS_EQUAL( icmpA.identifier(),  0x0500 );

	//check icmp sequence number
	//using b because it has orginal value
	QUNIT_IS_EQUAL( icmpB.sequenceNum(),  0xbf08 );
	//check set sequence number
	icmpA.setSequenceNum( 0xbf11 );
	QUNIT_IS_EQUAL( icmpA.sequenceNum(),  0xbf11 );

	//check generate checksum
	icmpA.generateChecksum();
}

#ifndef GLOBAL_SCOPE
int main()
{
	return IcmpTest( std::cerr ).run();
}
#endif
