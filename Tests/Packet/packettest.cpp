#include "packettest.h"
#include "../../Packet/packetBuilder.h"

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


  uint8_t inetBits[] = { 0x45, 0x00, 0x00, 0x34, 0xcd, 0x96, 0x40, 0x00, 0x40, 0x06, 0x43, 0x70, 0x0a, 0x0d, 0x25, 0x45,
  0xd0, 0x55, 0x2a, 0x16 };

  IPv4 ip( inetBits, 20 );

  uint8_t tcpBits[] = { 0xaf, 0x5a, 0x00, 0x50, 0xf4, 0x90, 0x12, 0x9e, 0xb8, 0xb7, 0x65, 0xe2, 0x80, 0x10, 0x00, 0x56,
  0xda, 0x81, 0x00, 0x00, 0x01, 0x01, 0x08, 0x0a, 0x00, 0x69, 0xcf, 0xc2, 0xc7, 0xdc, 0x04, 0xac };

  TCP tcp( tcpBits, 32 );

  uint8_t rawBits[] = {0x11, 0xAA, 0xFF};
  Raw raw( rawBits, 3 );

  Packet packet;
  packet.pushBackLink( ethernet1 );
  packet.pushBackInet( ip );
  packet.pushBackTrans( tcp );
  packet.pushBackApp( raw );

  Ethernet ethCopy = packet.getLink<Ethernet>();
  IPv4 ipCopy = packet.getInet<IPv4>();
  TCP tcpCopy = packet.getTrans<TCP>();
  Raw rawCopy = packet.getApp<Raw>();

  QCOMPARE( ethCopy.size(), 14 );
  QCOMPARE( ipCopy.size(), 20 );
  QCOMPARE( tcpCopy.size(), 32 );
  QCOMPARE( rawCopy.size(), 3 );
  QCOMPARE( packet.linkSize(), 1 );
  QCOMPARE( packet.inetSize(), 1 );
  QCOMPARE( packet.transSize(), 1 );
  QCOMPARE( packet.appSize(), 1 );
  QCOMPARE( packet.size(),  (14 + 20 + 32 + 3) );
  QCOMPARE( packet.makePacket().size(), (14 + 20 + 32 + 3) );


}


void PacketTest::testPacketBuilding()
{
    PacketBuilder pb;

    uint8_t bits[] = { 0x45, 0x00, 0x00, 0x51, 0x69, 0x1e, 0x40, 0x00, 0x40, 0x06, 0x03, 0x4b, 0x0a, 0xdd, 0x5b, 0xc1,
                       0x0a, 0xdd, 0x5c, 0xc3, 0xb1, 0xdd, 0x23, 0x28, 0xbc, 0x43, 0x1d, 0x35, 0x7d, 0x1f, 0x8b, 0x9d,
                       0xb0, 0x18, 0x00, 0x73, 0xf2, 0x5e, 0x00, 0x00, 0x01, 0x01, 0x08, 0x0a, 0x00, 0x0e, 0x77, 0x19,
                       0x2b, 0x74, 0x0e, 0x00, 0x01, 0x01, 0x05, 0x0a, 0x7d, 0x1f, 0x8b, 0x9e, 0x7d, 0x1f, 0x8b, 0xb9,
                       0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00 };

    Packet p = pb.build<IPv4>(bits, 81);

    IPv4 ip = p.getInet<IPv4>();
    TCP tcp = p.getTrans<TCP>();
    Raw raw = p.getApp<Raw>();

    QCOMPARE( ip.makePacket().size(), 20 );
    QCOMPARE( tcp.makePacket().size(), 44 ); //including options
    QCOMPARE( raw.makePacket().size(), 17 );




}


