
#include "Packet/Link/Ethernet/tst_ethernettest.h"
#include "Packet/Link/Ethernet/linktest.h"
#include "Packet/Link/Ethernet/mactest.h"
#include <QTest>

int main()
{
  EthernetTest ethernetTest;
  QTest::qExec( &ethernetTest );

  LinkTest linkTest;
  QTest::qExec( &linkTest );


  MacTest macTest;
  QTest::qExec( &macTest );

}
