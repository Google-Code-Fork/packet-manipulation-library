OBJS=threads.o parseCommas.o mutex.o commandLineParser.o
PACKETOBJS=../Packet/packet.o ../Packet/packetBuffer.o ../Packet/Link/ethernet.o ../Packet/Link/mac.o ../Packet/Link/link.o ../Packet/Inet/ipv4.o ../Packet/Inet/inet.o ../Packet/Trans/tcp.o ../Packet/Trans/udp.o ../Packet/Trans/trans.o ../Packet/App/raw.o ../Packet/App/app.o
CFLAGS=-ggdb
CXXFLAGS=$(CFLAGS)

all: $(OBJS) 

clean:
	 -rm -f *.o


