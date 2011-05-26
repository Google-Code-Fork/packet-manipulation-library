#-------------------------------------------------
#
# Project created by QtCreator 2011-05-11T03:14:44
#
#-------------------------------------------------

QT       -= core gui

TARGET = PacMan
TEMPLATE = lib

DEFINES += PACMAN_LIBRARY

SOURCES += \
    common/threads.cpp \
    common/stringUtils.cpp \
    common/semaphore.cpp \
    common/mutex.cpp \
    Device/devicesLookup.cpp \
    Device/device.cpp \
    Injector/injector.cpp \
    Packet/packetBuilder.cpp \
    Packet/packetBuffer.cpp \
    Packet/packet.cpp \
    Packet/App/staticBuffer.cpp \
    Packet/App/raw.cpp \
    Packet/App/dnsRecord.cpp \
    Packet/App/dnsQuestion.cpp \
    Packet/App/dnsPacket.cpp \
    Packet/App/arp.cpp \
    Packet/App/app.cpp \
    Packet/Inet/ipv6Address.cpp \
    Packet/Inet/ipv6.cpp \
    Packet/Inet/ipv4.cpp \
    Packet/Inet/inet.cpp \
    Packet/Inet/icmp.cpp \
    Packet/Link/mac.cpp \
    Packet/Link/link.cpp \
    Packet/Link/ethernet.cpp \
    Packet/Trans/udp.cpp \
    Packet/Trans/trans.cpp \
    Packet/Trans/tcpOptions.cpp \
    Packet/Trans/tcp.cpp \
    Sniffer/snifferData.cpp \
    Sniffer/sniffer.cpp \
    Sniffer/filterData.cpp \
    Sniffer/baseData.cpp

COMMON_HEADERS = \
    common/threads.h \
    common/stringUtils.h \
    common/smartPtr.h \
    common/helper.h 

DEVICE_HEADERS = \
    Device/devicesLookup.h \
    Device/device.h 

INJECTOR_HEADERS = \ 
    Injector/injector.h 

PACKET_HEADERS = \
    Packet/packetBuilder.h \
    Packet/packetBuffer.h \
    Packet/packet.h \
    Packet/encapsulateable.h 

APP_HEADERS = \
    Packet/App/staticBuffer.h \
    Packet/App/raw.h \
    Packet/App/http.h \
    Packet/App/dnsPacket.h \
    Packet/App/arp.h \
    Packet/App/appData.h \
    Packet/App/app.h 

INET_HEADERS = \
    Packet/Inet/ipv6Address.h \
    Packet/Inet/ipv6.h \
    Packet/Inet/ipv4.h \
    Packet/Inet/inetData.h \
    Packet/Inet/inet.h \
    Packet/Inet/icmp.h 

LINK_HEADERS = \
    Packet/Link/mac.h \
    Packet/Link/linkData.h \
    Packet/Link/link.h \
    Packet/Link/ethernet.h 

TRANS_HEADERS = \
    Packet/Trans/wsOption.h \
    Packet/Trans/udp.h \
    Packet/Trans/transData.h \
    Packet/Trans/trans.h \
    Packet/Trans/timeStampOption.h \
    Packet/Trans/tcpOptions.h \
    Packet/Trans/tcp.h \
    Packet/Trans/sackPermittedOption.h \
    Packet/Trans/sackOption.h \
    Packet/Trans/noopOption.h \
    Packet/Trans/mssOption.h \
    Packet/Trans/eolOption.h 

SNIFFER_HEADERS = \
    Sniffer/snifferData.h \
    Sniffer/sniffer.h \
    Sniffer/filterData.h \
    Sniffer/constants.h \
    Sniffer/baseData.h

HEADERS += \
	  $$COMMON_HEADERS \
		$$DEVICE_HEADERS \
		$$INJECTOR_HEADERS \ 
		$$PACKET_HEADERS \ 
		$$APP_HEADERS \
		$$INET_HEADERS \
		$$LINK_HEADERS \
    $$TRANS_HEADERS \
		$$SNIFFER_HEADERS


OTHER_FILES +=

sniffer_header_files.files = $$SNIFFER_HEADERS
sniffer_header_files.path = /usr/local/include/PacMan/Sniffer/
trans_header_files.files = $$TRANS_HEADERS
trans_header_files.path = /usr/local/include/PacMan/Packet/Trans/
link_header_files.files = $$LINK_HEADERS
link_header_files.path = /usr/local/include/PacMan/Packet/Link/
inet_header_files.files = $$INET_HEADERS
inet_header_files.path = /usr/local/include/PacMan/Packet/Inet/
app_header_files.files = $$APP_HEADERS
app_header_files.path = /usr/local/include/PacMan/Packet/App/
packet_header_files.files = $$PACKET_HEADERS
packet_header_files.path = /usr/local/include/PacMan/Packet/
device_header_files.files = $$DEVICE_HEADERS
device_header_files.path = /usr/local/include/PacMan/Device/
injector_header_files.files = $$INJECTOR_HEADERS
injector_header_files.path = /usr/local/include/PacMan/Injector/
common_header_files.files = $$COMMON_HEADERS
common_header_files.path = /usr/local/include/PacMan/common/

INSTALLS += sniffer_header_files trans_header_files link_header_files inet_header_files app_header_files packet_header_files device_header_files injector_header_files common_header_files
