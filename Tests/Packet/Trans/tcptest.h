#ifndef TCPTEST_H
#define TCPTEST_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Trans/tcp.h"
#include "../../../Packet/Trans/tcpOptions.h"
#include "../../../Packet/Trans/mssOption.h"
#include "../../../Packet/Trans/noopOption.h"
#include "../../../Packet/Trans/sackPermittedOption.h"

class TcpTest : public QObject
{
    Q_OBJECT
public:
    explicit TcpTest(QObject *parent = 0);

private Q_SLOTS:
  void testConstruction();
  void testConstruction2();
  void testOptions();
};

#endif // TCPTEST_H
