QT       += testlib

QT       -= gui

TARGET = unitTests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += Packet/Link/tst_ethernettest.cpp \
        main.cpp \
    ../common/threads.cpp \
    ../common/stringUtils.cpp \
    ../common/semaphore.cpp \
    ../common/mutex.cpp \
    ../Device/devicesLookup.cpp \
    ../Device/device.cpp \
    ../Injector/injector.cpp \
    ../Packet/packetBuilder.cpp \
    ../Packet/packetBuffer.cpp \
    ../Packet/packet.cpp \
    ../Packet/App/staticBuffer.cpp \
    ../Packet/App/raw.cpp \
    ../Packet/App/dnsRecord.cpp \
    ../Packet/App/dnsQuestion.cpp \
    ../Packet/App/dnsPacket.cpp \
    ../Packet/App/arp.cpp \
    ../Packet/App/app.cpp \
    ../Packet/Inet/ipv6Address.cpp \
    ../Packet/Inet/ipv6.cpp \
    ../Packet/Inet/ipv4.cpp \
    ../Packet/Inet/inet.cpp \
    ../Packet/Inet/icmp.cpp \
    ../Packet/Link/mac.cpp \
    ../Packet/Link/link.cpp \
    ../Packet/Link/ethernet.cpp \
    ../Packet/Trans/udp.cpp \
    ../Packet/Trans/trans.cpp \
    ../Packet/Trans/tcpOptions.cpp \
    ../Packet/Trans/tcp.cpp \
    ../Sniffer/snifferData.cpp \
    ../Sniffer/sniffer.cpp \
    ../Sniffer/filterData.cpp \
    ../Sniffer/baseData.cpp \
    Packet/Link/linktest.cpp \
    Packet/Link/mactest.cpp \
    Packet/App/arptest.cpp \
    Packet/App/rawtest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    Packet/Link/tst_ethernettest.h \
    ../common/threads.h \
    ../common/stringUtils.h \
    ../common/smartPtr.h \
    ../common/helper.h \
    ../Device/devicesLookup.h \
    ../Device/device.h \
    ../Injector/injector.h \
    ../Packet/packetBuilder.h \
    ../Packet/packetBuffer.h \
    ../Packet/packet.h \
    ../Packet/encapsulateable.h \
    ../Packet/App/staticBuffer.h \
    ../Packet/App/raw.h \
    ../Packet/App/http.h \
    ../Packet/App/dnsPacket.h \
    ../Packet/App/arp.h \
    ../Packet/App/appData.h \
    ../Packet/App/app.h \
    ../Packet/Inet/ipv6Address.h \
    ../Packet/Inet/ipv6.h \
    ../Packet/Inet/ipv4.h \
    ../Packet/Inet/inetData.h \
    ../Packet/Inet/inet.h \
    ../Packet/Inet/icmp.h \
    ../Packet/Link/mac.h \
    ../Packet/Link/linkData.h \
    ../Packet/Link/link.h \
    ../Packet/Link/ethernet.h \
    ../Packet/Trans/wsOption.h \
    ../Packet/Trans/udp.h \
    ../Packet/Trans/transData.h \
    ../Packet/Trans/trans.h \
    ../Packet/Trans/timeStampOption.h \
    ../Packet/Trans/tcpOptions.h \
    ../Packet/Trans/tcp.h \
    ../Packet/Trans/sackPermittedOption.h \
    ../Packet/Trans/sackOption.h \
    ../Packet/Trans/noopOption.h \
    ../Packet/Trans/mssOption.h \
    ../Packet/Trans/eolOption.h \
    ../Sniffer/snifferData.h \
    ../Sniffer/sniffer.h \
    ../Sniffer/filterData.h \
    ../Sniffer/constants.h \
    ../Sniffer/baseData.h \
    Packet/Link/linktest.h \
    Packet/Link/mactest.h \
    Packet/App/arptest.h \
    Packet/App/rawtest.h
#CXXFLAGS += -I../Packet/Link -I../Packet -I../Packet/Trans -I../Packet/App -I../Packet/Inet
LIBS += -lpcap
