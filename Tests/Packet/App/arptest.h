#ifndef ARPTEST_H
#define ARPTEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/App/arp.h"

class ArpTest : public QObject
{
    Q_OBJECT
public:
    explicit ArpTest(QObject *parent = 0);

private Q_SLOTS:
  void testIsArp();
  void testConstruction();
  void testSetFunctions();

};

#endif // ARPTEST_H
