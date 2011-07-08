#include "tst_ethernettest.h"

void EthernetTest::testType()
{
  Ethernet ethernet;
  QCOMPARE( ethernet.type(), ethernetProtocol::k_ip );
  ethernet.setType( ethernetProtocol::k_arp );
  QCOMPARE( ethernet.type(), ethernetProtocol::k_arp );
}

void EthernetTest::testPacketCreation()
{
  //14 bytes ethernet header taken from a wireshark dump
  uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
    0xf9, 0xfc, 0x6e, 0x08, 0x00 };

  //construct a ethernet header from bytes above
  Ethernet ethernet1( bits, 14 );

  std::vector< uint8_t > data = ethernet1.makePacket().vector();

  QCOMPARE( static_cast<uint16_t>(data[0]), (uint16_t) 0x00 );
  QCOMPARE( static_cast<uint16_t>(data[1]), (uint16_t) 0x24 );
  QCOMPARE( static_cast<uint16_t>(data[2]), (uint16_t) 0xe8 );
  QCOMPARE( static_cast<uint16_t>(data[3]), (uint16_t) 0xa4 );
  QCOMPARE( static_cast<uint16_t>(data[4]), (uint16_t) 0x57 );
  QCOMPARE( static_cast<uint16_t>(data[5]), (uint16_t) 0x5f );

  QCOMPARE( static_cast<uint16_t>(data[6]), (uint16_t) 0xa4 );
  QCOMPARE( static_cast<uint16_t>(data[7]), (uint16_t) 0xba );
  QCOMPARE( static_cast<uint16_t>(data[8]), (uint16_t) 0xdb );
  QCOMPARE( static_cast<uint16_t>(data[9]), (uint16_t) 0xf9 );
  QCOMPARE( static_cast<uint16_t>(data[10]), (uint16_t) 0xfc );
  QCOMPARE( static_cast<uint16_t>(data[11]), (uint16_t) 0x6e );

  QCOMPARE( static_cast<uint16_t>(data[12]), (uint16_t) 0x08 );
  QCOMPARE( static_cast<uint16_t>(data[13]), (uint16_t) 0x00 );
}

void EthernetTest::testConstruction()
{
  //14 bytes ethernet header taken from a wireshark dump
   uint8_t bits[] = { 0x00, 0x24, 0xe8, 0xa4, 0x57, 0x5f, 0xa4, 0xba, 0xdb,
     0xf9, 0xfc, 0x6e, 0x08, 0x00 };

   //construct a ethernet header from bytes above
   Ethernet ethernet1( bits, 14 );
   MACAddress destinationMac = ethernet1.destinationMAC();
   MACAddress sourceMac = ethernet1.sourceMAC();

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

   QCOMPARE( ethernet1.type(), (uint16_t) 0x0800 );

   //Create a vector to test alternate constructor
   std::vector< uint8_t > bytes;
   for( int i = 0; i < 14; ++i )
   {
     bytes.push_back( bits[i] );
   }
   //Construct a ethernet header from vector of bytes representing ethernet
   //header capture from wireshark
   Ethernet ethernet2( bytes );
   //Test that the types of each header is correct
   QCOMPARE( ethernet1.type(), ethernetProtocol::k_ip );
   QCOMPARE( ethernet2.type(), ethernetProtocol::k_ip );

   //Pulling out source Mac Addresses from headers
   MACAddress source1 = ethernet1.sourceMAC();
   MACAddress source2 = ethernet2.sourceMAC();

   //Both headers should be the same
   QVERIFY( source1 == source2 );

   //Pulling out source Mac Addresses from headers
   MACAddress destination1 = ethernet1.destinationMAC();
   MACAddress destination2 = ethernet2.destinationMAC();

   //Both headers should be the same
   QVERIFY( destination1 == destination2 );

   destinationMac = ethernet2.destinationMAC();
   sourceMac = ethernet2.sourceMAC();

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

   QCOMPARE( ethernet2.type(), (uint16_t) 0x0800 );

   Ethernet ethernet3(ethernet1);
   destinationMac = ethernet3.destinationMAC();
    sourceMac = ethernet3.sourceMAC();

    QCOMPARE( static_cast<uint16_t>(destinationMac.mac()[0]) , (uint16_t) 0x00 );
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

    QCOMPARE( ethernet3.type(), (uint16_t) 0x0800 );

    Ethernet ethernet4;
    ethernet4 = ethernet2;
    destinationMac = ethernet4.destinationMAC();
    sourceMac = ethernet4.sourceMAC();

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

    QCOMPARE( ethernet4.type(), (uint16_t) 0x0800 );

    ethernet4.setType( (uint16_t) 0xABCD );
    LinkData* link = new Ethernet;
    *((Ethernet*)link) = ethernet4;

    destinationMac = ((Ethernet*)link)->destinationMAC();
    sourceMac = ((Ethernet*)link)->sourceMAC();
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

    QCOMPARE( ((Ethernet*)link)->type(), (uint16_t) 0xABCD );
}

EthernetTest::EthernetTest()
{
}

void EthernetTest::testIsEthernet()
{
  Ethernet ethernet;
  QVERIFY( ethernet.isEthernet() );
}
