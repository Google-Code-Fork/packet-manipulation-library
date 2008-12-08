OBJS=injector.o
PACKETOBJS=../Packet/packetBuilder.o ../Packet/packetBuffer.o ../Packet/packet.o ../Packet/Link/ethernet.o ../Packet/Link/mac.o ../Packet/Link/link.o ../Packet/Inet/ipv4.o ../Packet/Inet/inet.o ../Packet/Trans/tcp.o ../Packet/Trans/udp.o ../Packet/Trans/trans.o ../Packet/App/raw.o ../Packet/App/app.o
DEVICEOBJS=../Device/devicesLookup.o ../Device/device.o
TESTOBJS=test.o 
CFLAGS=-ggdb 
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lpcap

all: $(OBJS)  test

clean:
	 -rm -f *.o

test: $(OBJS) $(TESTOBJS) $(PACKETOBJS) $(DEVICEOBJS)
	g++ $(LDFLAGS) $(OBJS) $(TESTOBJS) $(PACKETOBJS) $(DEVICEOBJS) -o $@
