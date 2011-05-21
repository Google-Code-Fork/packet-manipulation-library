#ifndef UDPTEST_H
#define UDPTEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Trans/udp.h"


class UdpTest : public QObject
{
    Q_OBJECT
public:
    explicit UdpTest(QObject *parent = 0);

private Q_SLOTS:
  void testConstruction();

};

#endif // UDPTEST_H
