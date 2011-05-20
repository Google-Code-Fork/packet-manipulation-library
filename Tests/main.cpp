
#include "Packet/Link/tst_ethernettest.h"
#include "Packet/Link/linktest.h"
#include "Packet/Link/mactest.h"
#include "Packet/App/arptest.h"
#include "Packet/App/rawtest.h"
#include <QTest>

int main()
{
  EthernetTest ethernetTest;
  QTest::qExec( &ethernetTest );

  LinkTest linkTest;
  QTest::qExec( &linkTest );

  MacTest macTest;
  QTest::qExec( &macTest );

  ArpTest arpTest;
  QTest::qExec( &arpTest );

  RawTest rawTest;
  QTest::qExec( &rawTest );
}
