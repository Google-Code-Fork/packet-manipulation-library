include ../../global.mk
INCLUDE=-I../../Device/ -I../ 
OBJS=../baseData.o ../sniffer.o ../filterData.o ../snifferData.o 
PACKETOBJS=../../Device/device.o ../../Device/devicesLookup.o ../../Packet/packetBuilder.o ../../Packet/packet.o ../../Packet/packetBuffer.o ../../Packet/Link/ethernet.o ../../Packet/Link/mac.o ../../Packet/Link/link.o ../../Packet/Inet/ipv4.o ../../Packet/Inet/inet.o ../../Packet/Trans/tcp.o ../../Packet/Trans/udp.o ../../Packet/Trans/trans.o  ../../common/threads.o ../../common/mutex.o ../../common/semaphore.o ../../Packet/Trans/tcpOptions.o ${APPOBJS}
TCPDUMP=$(PACKETOBJS) tcpDump.o
CFLAGS=-ggdb $(INCLUDE) -fPIC
CXXFLAGS=$(CFLAGS) 
PCAPLINK=-L/usr/lib/  
LDFLAGS=$(PCAPLINK) -lpthread -lpcap

all: $(OBJS) tcpdump

clean:
	 -rm -f *.o tcpdump

tcpdump: $(OBJS) $(TCPDUMP)
	g++ $(OBJS) $(TCPDUMP) $(LDFLAGS) -o $@	

options.o: options.h
tcpDump.o: tcpDump.cpp ../sniffer.h ../snifferData.h ../baseData.h \
  ../../common/threads.h ../filterData.h ../../Packet/packetBuilder.h \
  ../../Packet/packet.h ../../Packet/encapsulateable.h \
  ../../Packet/packetBuffer.h ../../Packet/Link/link.h \
  ../../Packet/Link/../encapsulateable.h ../../Packet/Link/linkData.h \
  ../../Packet/Link/../packetBuffer.h ../../Packet/Link/ethernet.h \
  ../../Packet/Link/mac.h ../../Packet/App/app.h \
  ../../Packet/App/appData.h ../../Packet/App/../packetBuffer.h \
  ../../Packet/App/../encapsulateable.h ../../Packet/App/raw.h \
  ../../Packet/Inet/inet.h ../../Packet/Inet/inetData.h \
  ../../Packet/Inet/../packetBuffer.h \
  ../../Packet/Inet/../encapsulateable.h ../../Packet/Inet/ipv4.h \
  ../../Packet/Trans/trans.h ../../Packet/Trans/transData.h \
  ../../Packet/Trans/../packetBuffer.h \
  ../../Packet/Trans/../encapsulateable.h ../../Packet/Trans/tcp.h \
  ../../Packet/Trans/udp.h ../../Packet/Link/ethernet.h \
  ../../Packet/Inet/ipv4.h ../../Packet/Trans/tcp.h \
  ../../Packet/Trans/udp.h ../../Packet/App/raw.h ../../Device/device.h \
  ../../Device/devicesLookup.h ../../Device/../common/threads.h options.h
