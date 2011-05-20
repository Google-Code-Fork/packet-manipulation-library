#ifndef TST_ETHERNETTEST_H
#define TST_ETHERNETTEST_H
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Link/ethernet.h"
#include "../../../Packet/Link/linkData.h"
#include "../../../Packet/Link/mac.h"

class EthernetTest : public QObject
{
    Q_OBJECT

public:
    EthernetTest();

private Q_SLOTS:
    void testIsEthernet();
    void testConstruction();
    void testPacketCreation();
    void testType();
};

#endif // TST_ETHERNETTEST_H
