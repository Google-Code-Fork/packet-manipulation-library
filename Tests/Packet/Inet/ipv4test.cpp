#include "ipv4test.h"
#include <string>


Ipv4Test::Ipv4Test(QObject *parent) :
  QObject(parent)
{

}

void Ipv4Test::testIsIpv4()
{
  IPv4 ip;
  QVERIFY( ip.isIPv4() );
}

void Ipv4Test::testIPv4String()
{
  IPv4Address ip = 0xAC102A03;
  std::string address = ip.toString();
  QCOMPARE( address, std::string( "172.16.42.3" ) );
}

void Ipv4Test::testPacketCreation()
{

  //20 bytes IPv4 header taken from a wireshark dump
  uint8_t bits[] = { 0x45, 0x00, 0x00, 0x30, 0x62, 0xd7, 0x40, 0x00, 0x80,
                     0x06, 0xf8, 0x7b, 0xa3, 0xf0, 0xa8, 0xe7, 0xc1, 0x6e, 0x91, 0x2e };

  //construct IPv4 header from bytes above
  IPv4 ipv4_1( bits, 20 );

  //copy
  IPv4 ipv4_2( ipv4_1 );

  //isIPv4
  QVERIFY( ipv4_1.isIPv4() );
  QVERIFY( ipv4_2.isIPv4() );

  //size
  QCOMPARE( ipv4_1.size(), ipv4_2.size() );
  QVERIFY( ipv4_1.size() == 20 );

  //version
  QVERIFY( ipv4_1.version() == 4);

  //setversion
  ipv4_1.setVersion(0x06);
  QVERIFY( ipv4_1.version() == 6);
  ipv4_1.setVersion(0x05);
  QVERIFY( ipv4_1.version() == 5);
  ipv4_1.setVersion(15);
  QVERIFY( ipv4_1.version() ==15);
  //change the version back to 4
  ipv4_1.setVersion(0x04);

  //headerLength
  QVERIFY( ipv4_1.headerLength() == 20 );

  //setHeaderLength
  ipv4_1.setHeaderLength(12);
  QVERIFY( ipv4_1.headerLength() == 12);
  ipv4_1.setHeaderLength(24);
  QVERIFY( ipv4_1.headerLength() == 24);
  //change the header length back to 20 (=5 words)
  ipv4_1.setHeaderLength(20);

  //totalLength
  QVERIFY( ipv4_1.totalLength() == 48 );

  //setTotalLength
  ipv4_1.setTotalLength(0x0040);
  QVERIFY( ipv4_1.totalLength() == 64 );
  //change the total length back to 48
  ipv4_1.setTotalLength(48);

  //identification
  QVERIFY( ipv4_1.identification() == 0x62d7 );

  //setIdentifaction
  ipv4_1.setIdentification(0x6666);
  QVERIFY( ipv4_1.identification() == 0x6666 );
  //change the identification field back to original (0x62d7)
  ipv4_1.setIdentification(0x62d7);

  //Flag - returns dontfragment flag (true|false)
  QVERIFY( ipv4_1.dontFragment() );
  //set dontfragment flag
  ipv4_1.setDontFragment( false );
  QVERIFY( ipv4_1.dontFragment() == false );
  //set dontfragment -> true
  ipv4_1.setDontFragment();
  QVERIFY( ipv4_1.dontFragment() );

  //Flag - returns moreFragment flag (true|false)
  QVERIFY( ipv4_1.moreFragments() == false );
  //set moreFragment flag to false
  ipv4_1.setMoreFragments( false );
  QVERIFY( ipv4_1.moreFragments() == false );
  //set moreFragment flag to true
  ipv4_1.setMoreFragments();
  QVERIFY( ipv4_1.moreFragments() );

  //check fragment offset field
  QVERIFY( ipv4_1.fragmentOffset() == 0x0000 );
  //set fragment offset field
  ipv4_1.setFragmentOffset( 0x0006 );
  QVERIFY( ipv4_1.fragmentOffset() == 0x0006 );

  //check ttl value
  QVERIFY( ipv4_1.ttl() == 128 );
  //set ttl value
  ipv4_1.setTtl( 0x60 );
  QVERIFY( ipv4_1.ttl() == 96 );
  // set back to 128
  ipv4_1.setTtl( 0x80 );

  //check protocol field
  QCOMPARE( ipv4_1.protocol(), ipProtocol::TCP );
  //set protocol field
  ipv4_1.setProtocol( ipProtocol::ICMP );
  QCOMPARE( ipv4_1.protocol(), ipProtocol::ICMP );


  //check checksum value (both are OK!)
  QVERIFY( ipv4_1.checksum() == 0xf87b );
  QVERIFY( ipv4_1.checksum() == 63611 );
  //set the checksum and check value
  ipv4_1.setChecksum( 0x33c3 );
  QVERIFY( ipv4_1.checksum() == 13251 );

  //correct values for source & destination IP addresses
  uint32_t correctSource = 0xa3f0a8e7;
  QVERIFY( ipv4_1.sourceAddress() == correctSource);
  uint32_t correctDestination = 0xc16e912e;
  QVERIFY( ipv4_1.destinationAddress() == correctDestination );
}
