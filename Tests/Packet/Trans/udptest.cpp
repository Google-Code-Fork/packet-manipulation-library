#include "udptest.h"
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Trans/udp.h"

UdpTest::UdpTest(QObject *parent) :
    QObject(parent)
{
}

void UdpTest::testConstruction()
{

  //8 bytes UDP header taken from wireshark dump
  uint8_t bits[] = { 0xd5, 0x1b, 0x00, 0x35, 0x00, 0x27, 0x4b, 0x15 };

  //construct UDP header from bytes above
  UDP udp1( bits, 8 );

  //copy UDP header
  UDP udp2( udp1 );

  //check source port
  QVERIFY( udp1.sourcePort() == 0xd51b );
  //check set source port
  udp1.setSourcePort( 0xd599 );
  QVERIFY( udp1.sourcePort() == 0xd599 );

  //check dest port
  QVERIFY( udp1.destinationPort() == 0x0035 );
  //check set dest source port
  udp1.setDestinationPort( 0x1111 );
  QVERIFY( udp1.destinationPort() == 0x1111 );

  //check checksum
  QVERIFY( udp1.checksum() == 0x4b15 );
  //check set checksum
  udp1.setChecksum( 0x4b11 );
  QVERIFY( udp1.checksum() == 0x4b11 );

  //check length
  QVERIFY( udp1.length() == 0x0027 );
  //set length
  udp1.setLength( 0x0030 );
  QVERIFY( udp1.length() == 0x0030 );

  //check size
  QVERIFY( udp1.size() == 8 );
  QCOMPARE( udp1.size(), udp2.size() );

  //check if UDP header
  QVERIFY( udp1.isUDP() );
}
