OBJS=device.o devicesLookup.o
PACKETOBJS=../Packet/packetBuilder.o ../Packet/packetBuffer.o ../Packet/packet.o ../Packet/Link/ethernet.o ../Packet/Link/mac.o ../Packet/Link/link.o ../Packet/Inet/ipv4.o ../Packet/Inet/inet.o ../Packet/Trans/tcp.o ../Packet/Trans/udp.o ../Packet/Trans/trans.o ../Packet/App/raw.o ../Packet/App/app.o
CFLAGS=-ggdb 
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lpcap
THIS=Device

all: $(OBJS) 

include:
	-mkdir ../include/$(THIS)
	-cp *.h ../include/$(THIS)

lib:
	cp *.o ../lib/

clean:
	 -rm -f *.o
