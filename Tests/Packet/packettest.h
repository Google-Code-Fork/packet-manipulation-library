#ifndef PACKETTEST_H
#define PACKETTEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../Packet/packet.h"


class PacketTest : public QObject
{
    Q_OBJECT
public:
    explicit PacketTest(QObject *parent = 0);

private Q_SLOTS:
  void testConstruction();
  void testPacketCreations();
  void testPacketBuilding();
};

#endif // PACKETTEST_H
