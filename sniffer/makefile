
INCLUDE=-I../Device/ 
OBJS=baseData.o sniffer.o filterData.o snifferData.o 
PACKETOBJS=../Device/device.o ../Device/devicesLookup.o ../Packet/packetBuilder.o ../Packet/packet.o ../Packet/packetBuffer.o ../Packet/Link/ethernet.o ../Packet/Link/mac.o ../Packet/Link/link.o ../Packet/Inet/ipv4.o ../Packet/Inet/inet.o ../Packet/Trans/tcp.o ../Packet/Trans/udp.o ../Packet/Trans/trans.o ../Packet/App/raw.o ../Packet/App/app.o ../common/threads.o ../common/mutex.o ../common/semaphore.o
TCPDUMP=$(PACKETOBJS) tcpDump.o
CFLAGS=-ggdb $(INCLUDE)
CXXFLAGS=$(CFLAGS) 
DIRECTORIES=example

all: $(OBJS) 
	for i in $(DIRECTORIES) ; do \
	( cd $$i ; make ) ; \
	done

clean:
	-rm -f *.o
	for i in $(DIRECTORIES) ; do \
	( cd $$i ; make clean ) ; \
	done

PCAPLINK=-L/usr/lib/  
LDFLAGS=$(PCAPLINK) -lpthread -lpcap

baseData.o: baseData.cpp baseData.h ../common/threads.h
baseData.o: baseData.h ../common/threads.h
constants.o: constants.h
filterData.o: filterData.cpp filterData.h ../common/threads.h baseData.h \
  ../Packet/packetBuilder.h ../Packet/packet.h \
  ../Packet/encapsulateable.h ../Packet/packetBuffer.h \
  ../Packet/Link/link.h ../Packet/Link/../encapsulateable.h \
  ../Packet/Link/linkData.h ../Packet/Link/../packetBuffer.h \
  ../Packet/Link/ethernet.h ../Packet/Link/mac.h ../Packet/App/app.h \
  ../Packet/App/appData.h ../Packet/App/../packetBuffer.h \
  ../Packet/App/../encapsulateable.h ../Packet/App/raw.h \
  ../Packet/Inet/inet.h ../Packet/Inet/inetData.h \
  ../Packet/Inet/../packetBuffer.h ../Packet/Inet/../encapsulateable.h \
  ../Packet/Inet/ipv4.h ../Packet/Trans/trans.h \
  ../Packet/Trans/transData.h ../Packet/Trans/../packetBuffer.h \
  ../Packet/Trans/../encapsulateable.h ../Packet/Trans/tcp.h \
  ../Packet/Trans/udp.h ../Packet/Link/ethernet.h ../Packet/Inet/ipv4.h \
  ../Packet/Trans/tcp.h ../Packet/Trans/udp.h ../Packet/App/raw.h
filterData.o: filterData.h ../common/threads.h baseData.h \
  ../Packet/packetBuilder.h ../Packet/packet.h \
  ../Packet/encapsulateable.h ../Packet/packetBuffer.h \
  ../Packet/Link/link.h ../Packet/Link/../encapsulateable.h \
  ../Packet/Link/linkData.h ../Packet/Link/../packetBuffer.h \
  ../Packet/Link/ethernet.h ../Packet/Link/mac.h ../Packet/App/app.h \
  ../Packet/App/appData.h ../Packet/App/../packetBuffer.h \
  ../Packet/App/../encapsulateable.h ../Packet/App/raw.h \
  ../Packet/Inet/inet.h ../Packet/Inet/inetData.h \
  ../Packet/Inet/../packetBuffer.h ../Packet/Inet/../encapsulateable.h \
  ../Packet/Inet/ipv4.h ../Packet/Trans/trans.h \
  ../Packet/Trans/transData.h ../Packet/Trans/../packetBuffer.h \
  ../Packet/Trans/../encapsulateable.h ../Packet/Trans/tcp.h \
  ../Packet/Trans/udp.h ../Packet/Link/ethernet.h ../Packet/Inet/ipv4.h \
  ../Packet/Trans/tcp.h ../Packet/Trans/udp.h ../Packet/App/raw.h
sniffer.o: sniffer.cpp sniffer.h snifferData.h baseData.h \
  ../common/threads.h filterData.h ../Packet/packetBuilder.h \
  ../Packet/packet.h ../Packet/encapsulateable.h ../Packet/packetBuffer.h \
  ../Packet/Link/link.h ../Packet/Link/../encapsulateable.h \
  ../Packet/Link/linkData.h ../Packet/Link/../packetBuffer.h \
  ../Packet/Link/ethernet.h ../Packet/Link/mac.h ../Packet/App/app.h \
  ../Packet/App/appData.h ../Packet/App/../packetBuffer.h \
  ../Packet/App/../encapsulateable.h ../Packet/App/raw.h \
  ../Packet/Inet/inet.h ../Packet/Inet/inetData.h \
  ../Packet/Inet/../packetBuffer.h ../Packet/Inet/../encapsulateable.h \
  ../Packet/Inet/ipv4.h ../Packet/Trans/trans.h \
  ../Packet/Trans/transData.h ../Packet/Trans/../packetBuffer.h \
  ../Packet/Trans/../encapsulateable.h ../Packet/Trans/tcp.h \
  ../Packet/Trans/udp.h ../Packet/Link/ethernet.h ../Packet/Inet/ipv4.h \
  ../Packet/Trans/tcp.h ../Packet/Trans/udp.h ../Packet/App/raw.h \
  ../Device/device.h ../Device/devicesLookup.h constants.h
snifferData.o: snifferData.cpp snifferData.h baseData.h \
  ../common/threads.h
snifferData.o: snifferData.h baseData.h ../common/threads.h
sniffer.o: sniffer.h snifferData.h baseData.h ../common/threads.h \
  filterData.h ../Packet/packetBuilder.h ../Packet/packet.h \
  ../Packet/encapsulateable.h ../Packet/packetBuffer.h \
  ../Packet/Link/link.h ../Packet/Link/../encapsulateable.h \
  ../Packet/Link/linkData.h ../Packet/Link/../packetBuffer.h \
  ../Packet/Link/ethernet.h ../Packet/Link/mac.h ../Packet/App/app.h \
  ../Packet/App/appData.h ../Packet/App/../packetBuffer.h \
  ../Packet/App/../encapsulateable.h ../Packet/App/raw.h \
  ../Packet/Inet/inet.h ../Packet/Inet/inetData.h \
  ../Packet/Inet/../packetBuffer.h ../Packet/Inet/../encapsulateable.h \
  ../Packet/Inet/ipv4.h ../Packet/Trans/trans.h \
  ../Packet/Trans/transData.h ../Packet/Trans/../packetBuffer.h \
  ../Packet/Trans/../encapsulateable.h ../Packet/Trans/tcp.h \
  ../Packet/Trans/udp.h ../Packet/Link/ethernet.h ../Packet/Inet/ipv4.h \
  ../Packet/Trans/tcp.h ../Packet/Trans/udp.h ../Packet/App/raw.h \
  ../Device/device.h ../Device/devicesLookup.h
