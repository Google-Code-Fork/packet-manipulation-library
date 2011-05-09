#include "packetTest.h"
#include "../packet.h"
PacketTest::PacketTest( std::ostream &out, int verboseLevel ) : qunit( out, verboseLevel)
{
}

int PacketTest::run()
{
	testConstruction();
	testPacketCreations();
	return qunit.errors();
}

void PacketTest::testConstruction()
{
}


void PacketTest::testPacketCreations()
{
	//14 bytes ethernet header taken from a wireshark dump 
	uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
		0xf9, 0xfc, 0x6e, 0x08, 0x00 };

	//construct a ethernet header from bytes above
	Ethernet ethernet1( bits, 14 );

  std::vector< uint8_t > data = ethernet1.makePacket().vector();

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[0]) , 0x00 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[1]), 0x24 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[2]), 0xe8 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[3]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[4]), 0x57 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[5]), 0x5f );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[6]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[7]), 0xba );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[8]), 0xdb );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[9]), 0xf9 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[10]), 0xfc );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[11]), 0x6e );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[12]), 0x08 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[13]), 0x00 );

	Packet p;
	p.pushBackLink( ethernet1 );
	Ethernet ethernet2 = p.getLink<Ethernet>();
	data = ethernet2.makePacket().vector();
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[0]) , 0x00 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[1]), 0x24 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[2]), 0xe8 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[3]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[4]), 0x57 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[5]), 0x5f );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[6]), 0xa4 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[7]), 0xba );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[8]), 0xdb );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[9]), 0xf9 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[10]), 0xfc );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[11]), 0x6e );

	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[12]), 0x08 );
	QUNIT_IS_EQUAL( static_cast<uint16_t>(data[13]), 0x00 );
}
#ifndef GLOBAL_SCOPE
int main()
{
	return PacketTest( std::cerr ).run();
}
#endif

