#include "icmptest.h"

IcmpTest::IcmpTest(QObject *parent) :
    QObject(parent)
{
}

void IcmpTest::testIsIcmp()
{
  ICMP icmp;
  QVERIFY( icmp.isICMP() );
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
  QVERIFY( icmpA.isICMP() );
  QVERIFY( icmpB.isICMP() );
  //check size of ICMP header in bytes
  QCOMPARE( icmpA.size(), icmpB.size() );
  QCOMPARE( icmpA.size(),  8 );

  //check ICMP type
  QVERIFY( icmpA.type() == 0x08 );
  QCOMPARE( icmpA.type(), icmpTypes::ICMP_ECHO_REQUEST );
  //check set ICMP type
  icmpA.setType( 0x05 );
  QVERIFY( icmpA.type() == 0x05 );
  icmpA.setType( icmpTypes::ICMP_DESTINATION_UNREACHABLE );
  QCOMPARE( icmpA.type(), icmpTypes::ICMP_DESTINATION_UNREACHABLE );

  //check ICMP code
  QVERIFY( icmpA.code() == 0x00 );
  //check set ICMP code
  icmpA.setCode( 0x01 );
  QVERIFY( icmpA.code() == 0x01 );

  //check checksum
  QVERIFY( icmpA.checksum() == 0x8c53 );
  //check set checksum
  icmpA.setChecksum( 0x1122 );
  QVERIFY( icmpA.checksum() == 0x1122 );

  //check header length
  icmpA.setType( icmpTypes::ICMP_ECHO_REQUEST ); //so that a and b are same size
  QCOMPARE( icmpA.headerLength(), icmpB.headerLength() );
  QCOMPARE( icmpA.headerLength(), 8 );


  //check icmp identifier (request)
  //using b because it has orginal value
  QCOMPARE( icmpB.identifier(), static_cast<uint16_t>( 0x0200 ) );
  //check set icmp identifier (request)
  icmpA.setIdentifier( 0x0500 );
  QCOMPARE( icmpA.identifier(),  static_cast<uint16_t>( 0x0500 ) );

  //check icmp sequence number
  //using b because it has orginal value
  QCOMPARE( icmpB.sequenceNum(), static_cast< uint16_t >( 0xbf08 ) );
  //check set sequence number
  icmpA.setSequenceNum( 0xbf11 );
  QCOMPARE( icmpA.sequenceNum(), static_cast< uint16_t >( 0xbf11 ) );

  //check generate checksum
  icmpA.generateChecksum();
}
