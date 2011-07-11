#include "arptest.h"
#include "../../../Packet/Link/mac.h"

ArpTest::ArpTest(QObject *parent) :
    QObject(parent)
{
}

void ArpTest::testSetFunctions()
{
    Arp arp2;

    arp2.setHardwareSize( hardwaresize::ETHERNET );
    arp2.setHardwareType(hardwaretype::ETHERNET);
    arp2.setOpcode(arpopcode::request);
    arp2.setProtocolSize( protocolsize::IP );
    arp2.setProtocolType( protocoltype::IP );
    arp2.setSenderIPAddress( IPv4Address("192.168.1.1").makePacket() );
    arp2.setTargetIPAddress( IPv4Address("172.16.23.1").makePacket() );
    arp2.setSenderMacAddress( MACAddress("DE:AD:BE:EF:DE:AD").makePacket() );
    arp2.setTargetMacAddress( MACAddress("CA:FE:BA:BE:BA:BE").makePacket() );

    //check to size of raw contents in bytes
    QVERIFY( arp2.size() == 28 );

    //check to see if arp
    QVERIFY( arp2.isArp() );

    //check to see if the hardware values are correct
    QVERIFY( arp2.hardwareType() == hardwaretype::ETHERNET );

    //check protocol
    QVERIFY( arp2.protocolType() == protocoltype::IP );

    //check hardware size
    QVERIFY( arp2.hardwareSize() == hardwaresize::ETHERNET);

    //check protocol size
    QVERIFY( arp2.protocolSize() == protocolsize::IP );
    arp2.setProtocolSize( protocolsize::IPv6 );
    QVERIFY( arp2.protocolSize() == protocolsize::IPv6 );

    //check opcode
    QVERIFY( arp2.opcode() == arpopcode::request );

    //check Sender MAC
    QVERIFY( arp2.senderMacAddress().vector() ==  MACAddress("DE:AD:BE:EF:DE:AD").makePacket().vector() );

    //check Sender IP
    QVERIFY( arp2.senderIPAddress().vector() == IPv4Address("192.168.1.1").makePacket().vector() );

    //check target MAC
    QVERIFY( arp2.targetIPAddress().vector() == IPv4Address("172.16.23.1").makePacket().vector() );

    //check target IP
    QVERIFY( arp2.targetMacAddress().vector() == MACAddress("CA:FE:BA:BE:BA:BE").makePacket().vector() );


}

void ArpTest::testConstruction()
{

  uint8_t bits[] = { 0x00, 0x01, 0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0x00, 0x25, 0x00, 0x4b, 0x5a, 0x7d, 0xc0, 0xa8, 0x01, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa8, 0x01, 0xdf };
  std::vector< uint8_t > senderMacAddress;
  senderMacAddress.push_back( 0x00 );
  senderMacAddress.push_back( 0x25 );
  senderMacAddress.push_back( 0x00 );
  senderMacAddress.push_back( 0x4b );
  senderMacAddress.push_back( 0x5a );
  senderMacAddress.push_back( 0x7d );
  std::vector< uint8_t > senderIPAddress;
  senderIPAddress.push_back( 0xc0 ); //192.168.1.88
  senderIPAddress.push_back( 0xa8 );
  senderIPAddress.push_back( 0x01 );
  senderIPAddress.push_back( 0x88 );

  std::vector< uint8_t > targetMacAddress;
  targetMacAddress.push_back( 0x00 );
  targetMacAddress.push_back( 0x00 );
  targetMacAddress.push_back( 0x00 );
  targetMacAddress.push_back( 0x00 );
  targetMacAddress.push_back( 0x00 );
  targetMacAddress.push_back( 0x00 );

  std::vector< uint8_t > targetIPAddress;
  targetIPAddress.push_back( 0xc0 ); //192.168.1.223;
  targetIPAddress.push_back( 0xa8 );
  targetIPAddress.push_back( 0x01 );
  targetIPAddress.push_back( 0xdf );

  //construct raw header from bytes above
  Arp arp1( bits, 28 );

  //copy constructor
  Arp arp2( arp1 );

  //check to size of raw contents in bytes
  QCOMPARE( arp1.size(), arp2.size() );
  QVERIFY( arp1.size() == 28 );

  //check to see if arp
  QVERIFY( arp1.isArp() );
  QVERIFY( arp2.isArp() );

  //check to see if the hardware values are correct
  QVERIFY( arp1.hardwareType() == hardwaretype::ETHERNET );
  QVERIFY( arp2.hardwareType() == hardwaretype::ETHERNET );

  //check protocol
  QVERIFY( arp1.protocolType() == protocoltype::IP );
  QVERIFY( arp2.protocolType() == protocoltype::IP );

  //check hardware size
  QVERIFY( arp1.hardwareSize() == hardwaresize::ETHERNET);
  QVERIFY( arp2.hardwareSize() == hardwaresize::ETHERNET);

  //check protocol size
  QVERIFY( arp1.protocolSize() == protocolsize::IP );
  QVERIFY( arp2.protocolSize() == protocolsize::IP );

  //check opcode
  QVERIFY( arp1.opcode() == arpopcode::request );
  QVERIFY( arp2.opcode() == arpopcode::request );

  //check Sender MAC
  QVERIFY( arp1.senderMacAddress().vector() == senderMacAddress );
  QVERIFY( arp2.senderMacAddress().vector() == senderMacAddress );

  //check Sender IP
  QVERIFY( arp1.senderIPAddress().vector() == senderIPAddress );
  QVERIFY( arp2.senderIPAddress().vector() == senderIPAddress );

  //check target MAC
  QVERIFY( arp1.targetMacAddress().vector() == targetMacAddress );
  QVERIFY( arp2.targetMacAddress().vector() == targetMacAddress );

  //check target IP
  QVERIFY( arp1.targetIPAddress().vector() == targetIPAddress );
  QVERIFY( arp2.targetIPAddress().vector() == targetIPAddress );
}

void ArpTest::testIsArp()
{
  Arp arp;
  QVERIFY( arp.isArp() );
  QCOMPARE( arp.isRaw(), false );
}

