#ifndef TESTRAW_H
#define TESTRAW_H

#include <QObject>
#include <QtCore/QString>
#include <QtTest/QtTest>
#include "../../../Packet/App/raw.h"

class RawTest : public QObject
{
    Q_OBJECT
public:
    explicit RawTest(QObject *parent = 0);

private Q_SLOTS:
  void testIsRaw();
  void testConstruction();
  void testData();

};

#endif // TESTRAW_H
