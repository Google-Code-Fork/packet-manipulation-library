#ifndef IPV4TEST_H
#define IPV4TEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Inet/ipv4.h"

class Ipv4Test : public QObject
{
    Q_OBJECT
public:
    explicit Ipv4Test(QObject *parent = 0);

private Q_SLOTS:
  void testIsIpv4();
  void testPacketCreation();
  void testIPv4String();

};

#endif // IPV4TEST_H
