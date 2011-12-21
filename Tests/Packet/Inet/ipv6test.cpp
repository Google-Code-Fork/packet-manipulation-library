#include "ipv6test.h"

Ipv6Test::Ipv6Test(QObject *parent) :
    QObject(parent)
{
}

void Ipv6Test::testPacketCreation()
{
  //40 bytes IPv6 header taken from a wireshark dump
  uint8_t bits[] = { 0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x06, 0x40, 0x20, 0x01,
                     0x04, 0x80, 0x04, 0x30, 0x00, 0x00, 0xc8, 0x8c, 0xf8, 0x49,
                     0x4c, 0xf9, 0xd5, 0x81, 0x20, 0x01, 0x04, 0x80, 0x04, 0x30,
                     0x00, 0x00, 0xc8, 0x8c, 0xf8, 0x49,  0x4c, 0xf9, 0xd5, 0x81 };

  //construct IPv6 header from bytes above
  IPv6 ipv6( bits, 40 );

  QCOMPARE( ipv6.version(), static_cast<uint8_t>(6) );
  QCOMPARE( ipv6.payloadLength(), static_cast<uint16_t>(24));
  QCOMPARE( ipv6.nextHeader(), static_cast<uint8_t>(0x06) ); //TCP
  QCOMPARE( ipv6.hopLimit(), static_cast<uint8_t>(0x40) ); //64 TTL
  std::cerr << ipv6.sourceAddress().toString() << std::endl;
  QCOMPARE( std::string( "2001:480:430:0:c88c:f849:4cf9:d581" ), ipv6.sourceAddress().toString() );
  QCOMPARE( std::string( "2001:480:430:0:c88c:f849:4cf9:d581" ), ipv6.destinationAddress().toString() );
}


void Ipv6Test::testGetSetFunctions()
{
  IPv6 ipv6;
  ipv6.setVersion( 1 );
  QCOMPARE( ipv6.version(), static_cast<uint8_t>(1) );
}
