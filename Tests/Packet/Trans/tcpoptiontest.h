#ifndef TCPOPTIONTEST_H
#define TCPOPTIONTEST_H

#include <QObect>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/Trans/tcpOptions.h"
#include "../../../Packet/Trans/timeStampOption.h"

class TcpOptionTest : public QObect
{
  Q_OBJECT
public:
  explicit TcpOptionTest(QObject *parent = 0);
  
signals:
  
public slots:

private Q_SLOTS:
  void testTimestamp();
  
};

#endif // TCPOPTIONTEST_H
