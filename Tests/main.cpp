
#include "Packet/Link/Ethernet/tst_ethernettest.h"
#include <QTest>

int main()
{
  EthernetTest ethernetTest;
  QTest::qExec( &ethernetTest );

}
