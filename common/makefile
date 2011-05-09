OBJS=threads.o mutex.o semaphore.o stringUtils.o
PACKETOBJS=../Packet/packet.o ../Packet/packetBuffer.o ../Packet/Link/ethernet.o ../Packet/Link/mac.o ../Packet/Link/link.o ../Packet/Inet/ipv4.o ../Packet/Inet/inet.o ../Packet/Trans/tcp.o ../Packet/Trans/udp.o ../Packet/Trans/trans.o ../Packet/App/raw.o ../Packet/App/app.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) 

lib:
	-cp *.o ../lib/

include:
	-mkdir ../include/common
	-cp *.h ../include/common/

clean:
	 -rm -f *.o


