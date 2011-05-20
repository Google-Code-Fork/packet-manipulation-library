QT       += testlib

QT       -= gui

TARGET = unitTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += Packet/Link/Ethernet/tst_ethernettest.cpp \
    ../Packet/Link/mac.cpp \
    ../Packet/Link/ethernet.cpp \
    ../Packet/packetBuffer.cpp \
    main.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Packet/Link/mac.h \
    ../Packet/Link/ethernet.h \
    ../Packet/packetBuffer.h \
    ../Packet/Link/linkData.h \
    Packet/Link/Ethernet/tst_ethernettest.h

#CXXFLAGS += -I../Packet/Link -I../Packet -I../Packet/Trans -I../Packet/App -I../Packet/Inet
