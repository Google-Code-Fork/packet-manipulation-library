#include "linktest.h"

LinkTest::LinkTest()
{
}

void LinkTest::testEthernet()
{
    Link link;
    //14 bytes ethernet header taken from a wireshark dump
    uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
            0xf9, 0xfc, 0x6e, 0x08, 0x00 };

    //construct a ethernet header from bytes above
    Ethernet ethernet( bits, 14 );
    QVERIFY( ethernet.isEthernet() );
    ethernet.setType( 0xABCD );
    link.set( ethernet );
    QVERIFY( link.is<Ethernet>( ) );
    Ethernet ethernet2 = link.get<Ethernet>();
MACAddress destinationMac = ethernet2.destinationMAC();
MACAddress sourceMac = ethernet2.sourceMAC();

QCOMPARE( static_cast<uint16_t>(destinationMac.mac()[0]), (uint16_t) 0x00 );
QCOMPARE( static_cast<uint16_t>(destinationMac.mac()[1]), (uint16_t) 0x24 );
QCOMPARE( static_cast<uint16_t>(destinationMac.mac()[2]), (uint16_t) 0xe8 );
QCOMPARE( static_cast<uint16_t>(destinationMac.mac()[3]), (uint16_t) 0xa4 );
QCOMPARE( static_cast<uint16_t>(destinationMac.mac()[4]), (uint16_t) 0x57 );
QCOMPARE( static_cast<uint16_t>(destinationMac.mac()[5]), (uint16_t) 0x5f );

QCOMPARE( static_cast<uint16_t>(sourceMac.mac()[0]), (uint16_t) 0xa4 );
QCOMPARE( static_cast<uint16_t>(sourceMac.mac()[1]), (uint16_t) 0xba );
QCOMPARE( static_cast<uint16_t>(sourceMac.mac()[2]), (uint16_t) 0xdb );
QCOMPARE( static_cast<uint16_t>(sourceMac.mac()[3]), (uint16_t) 0xf9 );
QCOMPARE( static_cast<uint16_t>(sourceMac.mac()[4]), (uint16_t) 0xfc );
QCOMPARE( static_cast<uint16_t>(sourceMac.mac()[5]), (uint16_t) 0x6e );

QCOMPARE( ethernet2.type(), (uint16_t) 0xABCD );


}
