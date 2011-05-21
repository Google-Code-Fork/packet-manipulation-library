#ifndef ICMPTEST_H
#define ICMPTEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Inet/icmp.h"

class IcmpTest : public QObject
{
    Q_OBJECT
public:
    explicit IcmpTest(QObject *parent = 0);

private Q_SLOTS:
  void testIsIcmp();
  void testConstruction();

};

#endif // ICMPTEST_H
