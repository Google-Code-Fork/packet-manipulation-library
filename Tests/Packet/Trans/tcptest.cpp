#include "tcptest.h"

TcpTest::TcpTest(QObject *parent) :
  QObject(parent)
{
}

void TcpTest::testConstruction()
{
  //20 bytes tcp header taken from wireshark dump
  uint8_t bits[] = { 0x00, 0x50, 0x60, 0x5d, 0x48, 0x5b, 0x27, 0xa6, 0xd3,
                     0xa5, 0xeb, 0xac, 0x50, 0x12, 0x16, 0x58, 0xd6, 0x59, 0x00, 0x00 };

  //construct tcp header from bytes above
  TCP tcp_1( bits, 20 );

  //copy tcp header
  TCP tcp_2( tcp_1 );

  //check is tcp
  QVERIFY( tcp_1.isTCP() );
  QVERIFY( tcp_2.isTCP() );

  //check source port
  QVERIFY( tcp_1.sourcePort() == 0x0050 );
  //check set source port
  tcp_1.setSourcePort( 0x0099 );
  QVERIFY( tcp_1.sourcePort() == 0x0099 );

  //check dest port
  QVERIFY( tcp_1.destinationPort() == 0x605d );
  //check set dest port
  tcp_1.setDestinationPort( 0x0666 );
  QVERIFY( tcp_1.destinationPort() == 0x0666 );

  //check seq #
  QVERIFY( tcp_1.sequenceNumber() == 0x485b27a6 );
  //check seq #
  tcp_1.setSequenceNumber( 0x40506070 );
  QVERIFY( tcp_1.sequenceNumber() == 0x40506070 );

  //check ack #
  QVERIFY( tcp_1.acknowledgementNumber() == 0xd3a5ebac );
  //check set ack #
  tcp_1.setAcknowledgementNumber( 0x11223344 );
  QVERIFY( tcp_1.acknowledgementNumber() == 0x11223344 );

  //check data offset
  QVERIFY( tcp_1.dataOffset() == 20 );
  //check set data offset
  tcp_1.setDataOffset( 28 );
  QVERIFY( tcp_1.dataOffset() == 28 );

  //check return reserved data after data offset
  QVERIFY( tcp_1.x2() == 0x00 );
  //check set reserved data
  tcp_1.setX2( 0x01 );
  QVERIFY( tcp_1.x2() == 0x01 );

  //check CWR flag
  QVERIFY( tcp_1.CWR_Flag() == false );
  //check set CWR flag
  tcp_1.setCWR_Flag( true );
  QVERIFY( tcp_1.CWR_Flag() );
  tcp_1.setCWR_Flag( false );
  QVERIFY( tcp_1.CWR_Flag() == false );
  //set flag to true
  tcp_1.setCWR_Flag();
  QVERIFY( tcp_1.CWR_Flag() );

  //check ECE flag
  QVERIFY( tcp_1.ECE_Flag() == false );
  //check set ECE flag
  tcp_1.setECE_Flag( true );
  QVERIFY( tcp_1.ECE_Flag() );
  tcp_1.setECE_Flag( false );
  QVERIFY( tcp_1.ECE_Flag() == false );
  //set flag to true
  tcp_1.setECE_Flag();
  QVERIFY( tcp_1.ECE_Flag() );

  //check URG flag
  QVERIFY( tcp_1.URG_Flag() == false );
  //check set URG flag
  tcp_1.setURG_Flag( true );
  QVERIFY( tcp_1.URG_Flag() );
  tcp_1.setURG_Flag( false );
  QVERIFY( tcp_1.URG_Flag() == false );
  //set flag to true
  tcp_1.setURG_Flag();
  QVERIFY( tcp_1.URG_Flag() );

  //check ACK flag
  QVERIFY( tcp_1.ACK_Flag() );
  //check set ACK flag
  tcp_1.setACK_Flag( false );
  QVERIFY( tcp_1.ACK_Flag() == false );
  tcp_1.setACK_Flag( true );
  QVERIFY( tcp_1.ACK_Flag() );
  tcp_1.setACK_Flag( false ); //set back to false
  //set flag to true
  tcp_1.setACK_Flag();
  QVERIFY( tcp_1.ACK_Flag() );

  //check PSH flag
  QVERIFY( tcp_1.PSH_Flag() == false );
  //check set PSH flag
  tcp_1.setPSH_Flag( true );
  QVERIFY( tcp_1.PSH_Flag() );
  tcp_1.setPSH_Flag( false );
  QVERIFY( tcp_1.PSH_Flag() == false );
  //set flag to true
  tcp_1.setPSH_Flag();
  QVERIFY( tcp_1.PSH_Flag() );

  //check RST flag
  QVERIFY( tcp_1.RST_Flag() == false );
  //check set RST flag
  tcp_1.setRST_Flag( true );
  QVERIFY( tcp_1.RST_Flag() );
  tcp_1.setRST_Flag( false );
  QVERIFY( tcp_1.RST_Flag() == false );
  //set flag to true
  tcp_1.setRST_Flag();
  QVERIFY( tcp_1.RST_Flag() );

  //check SYN flag
  QVERIFY( tcp_1.SYN_Flag() );
  //check set SYN flag
  tcp_1.setSYN_Flag( false );
  QVERIFY( tcp_1.SYN_Flag() == false );
  tcp_1.setSYN_Flag( true );
  QVERIFY( tcp_1.SYN_Flag() );
  tcp_1.setSYN_Flag( false ); //set back to false
  //set flag to true
  tcp_1.setSYN_Flag();
  QVERIFY( tcp_1.SYN_Flag() );

  //check FIN flag
  QVERIFY( tcp_1.FIN_Flag() == false );
  //check set FIN flag
  tcp_1.setFIN_Flag( true );
  QVERIFY( tcp_1.FIN_Flag() );
  tcp_1.setFIN_Flag( false );
  QVERIFY( tcp_1.FIN_Flag() == false );
  //set flag to true
  tcp_1.setFIN_Flag();
  QVERIFY( tcp_1.FIN_Flag() );

  //check then set window size
  QVERIFY( tcp_1.windowSize() == 0x1658 );
  tcp_1.setWindowSize( 0x1111 );
  QVERIFY( tcp_1.windowSize() == 0x1111 );

  //check then set checksum
  QVERIFY( tcp_1.checksum() == 0xd659 );
  tcp_1.setChecksum( 0xd666 );
  QVERIFY( tcp_1.checksum() == 0xd666 );

  //check then set urgent pointer
  QVERIFY( tcp_1.urgentPointer() == 0x0000 );
  tcp_1.setUrgentPointer( 0x0001 );
  QVERIFY( tcp_1.urgentPointer() == 0x0001 );

  //check the size
  QCOMPARE( tcp_1.size(), tcp_2.size() );
  QVERIFY( tcp_1.size() == 20 );
}

void TcpTest::testOptions()
{
  //28 bytes tcp header taken from wireshark dump
  //(min header size = 20bytes; max size = 60bytes)
          uint8_t bits[] = { 0x05, 0xde, 0x00, 0x50, 0xa9, 0xde, 0x0d, 0xd5, 0x00,
                  0x00, 0x00, 0x00, 0x60, 0x02, 0x40, 0x00, 0x37, 0xa4, 0x00, 0x00, 0x02,
                  0x04, 0x05, 0xa0 };

  //construct tcp header from bytes above
  TCP tcp_3( bits, 24 );

  //copy tcp header
  TCP tcp_3A( tcp_3 );

  //check size
  QVERIFY( tcp_3.size() == 24 );
  //check size of copy
  QVERIFY( tcp_3A.size() == 24 );
  //compare sizes
  QCOMPARE( tcp_3.size(), tcp_3A.size() );

  //check erase all options
  tcp_3.clearOptions();
  tcp_3A.clearOptions();

  QCOMPARE( tcp_3.size(), tcp_3A.size() );

  //add Maximum Segment Size option
  SmartPtr< TCPOption > mssOption = new MSSOption();
  tcp_3.addOption( mssOption );
  QVERIFY( tcp_3.size() == 24 );

  //add NOP Option
  tcp_3.clearOptions();
  SmartPtr< TCPOption > noopOption = new NOOPOption();
  tcp_3.addOption( noopOption );
  QVERIFY( tcp_3.size() == 21 );

  //add Sack Permitted option
  tcp_3.clearOptions();
  SmartPtr< TCPOption > sackPermittedOption = new SACKPremittedOption();
  tcp_3.addOption( sackPermittedOption );
  QVERIFY( tcp_3.size() == 22 );

  //add Time Stamp option
  tcp_3.clearOptions();
  SmartPtr< TCPOption > timeStampOption = new TimeStampOption();
  tcp_3.addOption( timeStampOption );
  QVERIFY( tcp_3.size() == 30 );

  //add WSOPT - Window Scale option
  tcp_3.clearOptions();
  SmartPtr< TCPOption > wsOption = new WSOption();
  tcp_3.addOption( wsOption );
  QVERIFY( tcp_3.size() == 23 );

  //add Sack option
  //method 1
  tcp_3.clearOptions();
  SmartPtr< TCPOption > sackOption = new SACKOption();
  tcp_3.addOption( sackOption );
  QVERIFY( tcp_3.size() == 22 );

  //add eolOption
  tcp_3.clearOptions();
  SmartPtr< TCPOption > eolOption = new EOLOption();
  tcp_3.addOption( eolOption );
  QVERIFY( tcp_3.size() != tcp_3A.size() );
}
