#include "testArp.h"

ARPTest::ARPTest( std::ostream &out, int verboseLevel ) : qunit(
		out, verboseLevel)
{
}

int ARPTest::run()
{
	testIsARP();
	testConstruction();
	return qunit.errors();
}

void ARPTest::testIsARP()
{
	Arp arp;
	QUNIT_IS_TRUE( arp.isArp() );
	QUNIT_IS_FALSE( arp.isRaw() );
}

void ARPTest::testConstruction()
{
	uint8_t bits[] = { 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x25, 0x00, 0x4b, 0x5a, 0x7d, 0xc0, 0xa8, 0x01, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa8, 0x01, 0xdf };

	//construct raw header from bytes above
	Arp arp1( bits, 28 );

	//copy constructor
	Arp arp2( arp1 );

	//check to size of raw contents in bytes
	QUNIT_IS_EQUAL( arp1.size(), arp2.size() );
	QUNIT_IS_TRUE( arp1.size() == 28 );

	//check to see if raw
	QUNIT_IS_TRUE( arp1.isArp() );
	QUNIT_IS_TRUE( arp2.isArp() );

	//check to see if the hardware values are correct
	QUNIT_IS_TRUE( arp1.hardwareType() == hardwaretype::ETHERNET );
	QUNIT_IS_TRUE( arp2.hardwareType() == hardwaretype::ETHERNET );

	//check protocol
	QUNIT_IS_TRUE( arp1.protocolType() == protocoltype::IP );
	QUNIT_IS_TRUE( arp2.protocolType() == protocoltype::IP );

	//check hardware size
	QUNIT_IS_TRUE( arp1.hardwareSize() == hardwaresize::ETHERNET);
	QUNIT_IS_TRUE( arp2.hardwareSize() == hardwaresize::ETHERNET);

	//check protocol size
	QUNIT_IS_TRUE( arp1.protocolSize() == protocolsize::IP );
	QUNIT_IS_TRUE( arp2.protocolSize() == protocolsize::IP );


}

#ifndef GLOBAL_SCOPE
int main()
{
	return ARPTest ( std::cerr ).run();
}
#endif
