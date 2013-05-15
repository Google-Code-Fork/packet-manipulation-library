#include "rawtest.h"

RawTest::RawTest(QObject *parent) :
    QObject(parent)
{
}

void RawTest::testConstruction()
{
  //25 bytes raw data taken from wireshark
  uint8_t bits[] = { 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x32, 0x00, 0x5c,
          0x4d, 0x41, 0x49, 0x4c, 0x53, 0x4c, 0x4f, 0x54, 0x5c, 0x42, 0x52, 0x4f, 0x57, 0x53,
          0x45, 0x00 };

  //construct raw header from bytes above
  Raw raw1( bits, 25 );

  //copy constructor
  Raw raw2( raw1 );

  //check to size of raw contents in bytes
  QCOMPARE( raw1.size(), raw2.size() );
  QVERIFY( raw1.size() == 25 );

  //check to see if raw
  QVERIFY( raw1.isRaw() );
}

void RawTest::testIsRaw()
{
  Raw raw;
  QVERIFY( raw.isRaw() );
}

void RawTest::testData()
{
  
  std::vector< uint8_t > data;
  data.push_back( 'a' );
  data.push_back( 'b' );
  data.push_back( 'c' );

  Raw raw;
  raw.setData( data );
  QVERIFY( raw.size() == 3 );
  QVERIFY(raw.data()[0] == 'a');
  QVERIFY(raw.data()[1] == 'b');
  QVERIFY(raw.data()[2] == 'c');

}
