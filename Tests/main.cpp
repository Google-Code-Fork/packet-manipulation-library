
#include "Packet/Link/tst_ethernettest.h"
#include "Packet/Link/linktest.h"
#include "Packet/Link/mactest.h"
#include "Packet/App/arptest.h"
#include "Packet/App/rawtest.h"
#include "Packet/Trans/tcptest.h"
#include "Packet/Trans/udptest.h"
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

  return returnCode;
}
