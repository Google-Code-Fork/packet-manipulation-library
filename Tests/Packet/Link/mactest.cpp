#include "mactest.h"

MacTest::MacTest(QObject *parent) :
    QObject(parent)
{
}

void MacTest::testConstruction()
{
  MACAddress mac1;
  std::vector< uint8_t > addressbytes;
  addressbytes.push_back( 0xDE );
  addressbytes.push_back( 0xAD );
  addressbytes.push_back( 0xBE );
  addressbytes.push_back( 0xEF );
  addressbytes.push_back( 0x20 );
  addressbytes.push_back( 0x10 );
  mac1.setMACAddress( addressbytes );
  MACAddress mac2( addressbytes );
  MACAddress mac3( mac2 );
  uint8_t addressByteArray[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x20, 0x10 };
  MACAddress mac4( addressByteArray );

  QVERIFY( mac1 == mac2 );
  QVERIFY( mac1 == mac3 );
  QVERIFY( mac1 == mac4 );

  uint8_t macaddress[6];
  mac1.getMAC( macaddress );
  for( uint32_t i = 0; i < 6; ++i )
  {
          QVERIFY( macaddress[i] == addressByteArray[i]);
  }
}
