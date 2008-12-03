
PCAPLIBS=-I/usr/lib/ -I/usr/include  
OBJS=baseData.o sniffer.o filterData.o snifferData.o 
PACKETOBJS=../Packet/packetBuilder.o ../Packet/packet.o ../Packet/packetBuffer.o ../Packet/Link/ethernet.o ../Packet/Link/mac.o ../Packet/Link/link.o ../Packet/Inet/ipv4.o ../Packet/Inet/inet.o ../Packet/Trans/tcp.o ../Packet/Trans/udp.o ../Packet/Trans/trans.o ../Packet/App/raw.o ../Packet/App/app.o ../common/threads.o ../common/parseCommas.o ../common/mutex.o ../common/commandLineParser.o ../common/semaphore.o
TESTOBJS=$(PACKETOBJS) testSniffer.o 
TCPDUMP=$(PACKETOBJS) tcpDump.o
CFLAGS=-ggdb
CXXFLAGS=$(CFLAGS)

all: $(OBJS) tcpDump

clean:
	 -rm -f *.o

PCAPLINK=-L/usr/lib/  
LDFLAGS=$(PCAPLINK) -lpthread -lpcap

tcpDump: $(OBJS) $(TCPDUMP)
	g++ $(LDFLAGS) $(OBJS) $(TCPDUMP) -o $@

baseData.o: baseData.cpp baseData.h ../common/threads.h
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
  constants.h ../common/parseCommas.h
snifferData.o: snifferData.cpp snifferData.h baseData.h \
  ../common/threads.h
tcpDump.o: tcpDump.cpp sniffer.h snifferData.h baseData.h \
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
  ../common/commandLineParser.h ../common/parseCommas.h
testSniffer.o: testSniffer.cpp sniffer.h snifferData.h baseData.h \
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
  ../common/commandLineParser.h ../common/parseCommas.h
baseData.o: baseData.h ../common/threads.h
constants.o: constants.h
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
  ../Packet/Trans/tcp.h ../Packet/Trans/udp.h ../Packet/App/raw.h
