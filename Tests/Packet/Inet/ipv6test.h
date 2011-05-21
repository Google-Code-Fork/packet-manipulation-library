#ifndef IPV6TEST_H
#define IPV6TEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Inet/ipv6.h"
#include "../../../Packet/Inet/ipv6Address.h"

class Ipv6Test : public QObject
{
    Q_OBJECT
public:
    explicit Ipv6Test(QObject *parent = 0);

private Q_SLOTS:
  void testPacketCreation();

};

#endif // IPV6TEST_H
