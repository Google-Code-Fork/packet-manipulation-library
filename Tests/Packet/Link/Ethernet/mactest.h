#ifndef MACTEST_H
#define MACTEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../../Packet/Link/ethernet.h"
#include "../../../../Packet/Link/linkData.h"
#include "../../../../Packet/Link/mac.h"
#include "../../../../Packet/Link/link.h"
class MacTest : public QObject
{
    Q_OBJECT
public:
    explicit MacTest(QObject *parent = 0);

private Q_SLOTS:
        void testConstruction();


};

#endif // MACTEST_H
