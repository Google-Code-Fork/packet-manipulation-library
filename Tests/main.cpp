
#include "Packet/Link/tst_ethernettest.h"
#include "Packet/Link/linktest.h"
#include "Packet/Link/mactest.h"
#include "Packet/App/arptest.h"
#include "Packet/App/rawtest.h"
#include "Packet/Trans/tcptest.h"
#include "Packet/Trans/udptest.h"
#include "Packet/Inet/ipv4test.h"
#include "Packet/Inet/icmptest.h"
#include "Packet/Inet/ipv6test.h"
#include <QTest>

int main()
{
  int returnCode = 0;

  EthernetTest ethernetTest;
  returnCode += QTest::qExec( &ethernetTest );

  LinkTest linkTest;
  returnCode += QTest::qExec( &linkTest );

  MacTest macTest;
  returnCode += QTest::qExec( &macTest );

  ArpTest arpTest;
  returnCode += QTest::qExec( &arpTest );

  RawTest rawTest;
  returnCode += QTest::qExec( &rawTest );

  TcpTest tcpTest;
  returnCode += QTest::qExec( &tcpTest );

  UdpTest udpTest;
  returnCode += QTest::qExec( &udpTest );

  Ipv4Test ipv4Test;
  returnCode += QTest::qExec( &ipv4Test );

  IcmpTest icmpTest;
  returnCode += QTest::qExec( &icmpTest );

  Ipv6Test ipv6Test;
  returnCode += QTest::qExec( &ipv6Test );


  return returnCode;
}
