#include "linkTest.h"

LinkTest::LinkTest( std::ostream &out, int verboseLevel ) : qunit( out, verboseLevel)
{
}

int LinkTest::run()
{
	testEthernet();
	return qunit.errors();
}

void LinkTest::testEthernet()
{
	Link link;
	//14 bytes ethernet header taken from a wireshark dump 
	uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
		0xf9, 0xfc, 0x6e, 0x08, 0x00 };

	//construct a ethernet header from bytes above
	Ethernet ethernet( bits, 14 );
	QUNIT_IS_TRUE( ethernet.isEthernet() );
	ethernet.setType( 0xABCD );
	link.set( ethernet );
	QUNIT_IS_TRUE( link.is<Ethernet>( ) );
	Ethernet ethernet2 = link.get<Ethernet>();
  MACAddress destinationMac = ethernet2.destinationMAC();
  MACAddress sourceMac = ethernet2.sourceMAC();

  QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[0]) , 0x00 );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[1]), 0x24 );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[2]), 0xe8 );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[3]), 0xa4 );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[4]), 0x57 );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(destinationMac.mac()[5]), 0x5f );

  QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[0]), 0xa4 );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[1]), 0xba );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[2]), 0xdb );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[3]), 0xf9 );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[4]), 0xfc );
  QUNIT_IS_EQUAL( static_cast<uint16_t>(sourceMac.mac()[5]), 0x6e );

  QUNIT_IS_EQUAL( ethernet2.type(), 0xABCD );
	

}

#ifndef GLOBAL_SCOPE
int main()
{
	return LinkTest( std::cerr ).run();
}
#endif

