#include "packettest.h"

PacketTest::PacketTest(QObject *parent) :
  QObject(parent)
{
}

void PacketTest::testConstruction()
{
  QWARN( "Unit TEST for testing Packet construction not written" );
}

void PacketTest::testPacketCreations()
{
  //14 bytes ethernet header taken from a wireshark dump
  uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
                     0xf9, 0xfc, 0x6e, 0x08, 0x00 };

  //construct a ethernet header from bytes above
  Ethernet ethernet1( bits, 14 );

  std::vector< uint8_t > data = ethernet1.makePacket().vector();

  QCOMPARE( static_cast<uint16_t>(data[0]) , static_cast<uint16_t>( 0x00 ));
  QCOMPARE( static_cast<uint16_t>(data[1]), static_cast<uint16_t>( 0x24 ));
  QCOMPARE( static_cast<uint16_t>(data[2]), static_cast<uint16_t>( 0xe8 ));
  QCOMPARE( static_cast<uint16_t>(data[3]), static_cast<uint16_t>( 0xa4 ));
  QCOMPARE( static_cast<uint16_t>(data[4]), static_cast<uint16_t>( 0x57 ));
  QCOMPARE( static_cast<uint16_t>(data[5]), static_cast<uint16_t>( 0x5f ));

  QCOMPARE( static_cast<uint16_t>(data[6]), static_cast<uint16_t>( 0xa4 ));
  QCOMPARE( static_cast<uint16_t>(data[7]), static_cast<uint16_t>( 0xba ));
  QCOMPARE( static_cast<uint16_t>(data[8]), static_cast<uint16_t>( 0xdb ));
  QCOMPARE( static_cast<uint16_t>(data[9]), static_cast<uint16_t>( 0xf9 ));
  QCOMPARE( static_cast<uint16_t>(data[10]), static_cast<uint16_t>( 0xfc ));
  QCOMPARE( static_cast<uint16_t>(data[11]), static_cast<uint16_t>( 0x6e ));

  QCOMPARE( static_cast<uint16_t>(data[12]), static_cast<uint16_t>( 0x08 ));
  QCOMPARE( static_cast<uint16_t>(data[13]), static_cast<uint16_t>( 0x00 ));

  Packet p;
  p.pushBackLink( ethernet1 );
  Ethernet ethernet2 = p.getLink<Ethernet>();
  data = ethernet2.makePacket().vector();
  QCOMPARE( static_cast<uint16_t>(data[0]) , static_cast<uint16_t>( 0x00 ));
  QCOMPARE( static_cast<uint16_t>(data[1]), static_cast<uint16_t>( 0x24 ));
  QCOMPARE( static_cast<uint16_t>(data[2]), static_cast<uint16_t>( 0xe8 ));
  QCOMPARE( static_cast<uint16_t>(data[3]), static_cast<uint16_t>( 0xa4 ));
  QCOMPARE( static_cast<uint16_t>(data[4]), static_cast<uint16_t>( 0x57 ));
  QCOMPARE( static_cast<uint16_t>(data[5]), static_cast<uint16_t>( 0x5f ));

  QCOMPARE( static_cast<uint16_t>(data[6]), static_cast<uint16_t>( 0xa4 ));
  QCOMPARE( static_cast<uint16_t>(data[7]), static_cast<uint16_t>( 0xba ));
  QCOMPARE( static_cast<uint16_t>(data[8]), static_cast<uint16_t>( 0xdb ));
  QCOMPARE( static_cast<uint16_t>(data[9]), static_cast<uint16_t>( 0xf9 ));
  QCOMPARE( static_cast<uint16_t>(data[10]), static_cast<uint16_t>( 0xfc ));
  QCOMPARE( static_cast<uint16_t>(data[11]), static_cast<uint16_t>( 0x6e ));

  QCOMPARE( static_cast<uint16_t>(data[12]), static_cast<uint16_t>( 0x08 ));
  QCOMPARE( static_cast<uint16_t>(data[13]), static_cast<uint16_t>( 0x00 ));

}
