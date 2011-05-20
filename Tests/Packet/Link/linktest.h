#ifndef LINKTEST_H
#define LINKTEST_H
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../../Packet/Link/ethernet.h"
#include "../../../../Packet/Link/linkData.h"
#include "../../../../Packet/Link/mac.h"
#include "../../../../Packet/Link/link.h"

class LinkTest : public QObject
{
        Q_OBJECT
public:
    LinkTest();

private Q_SLOTS:
        void testEthernet();
};

#endif // LINKTEST_H
