OBJS=ipv4.o inet.o icmp.o ../packetBuffer.o ../packet.o
PACKETBUILDEROBJS=../packetBuilder.o ../Link/ethernet.o ../Link/mac.o ../Link/link.o ../Trans/udp.o ../Trans/tcp.o ../Trans/tcpOptions.o ../Trans/trans.o ../App/app.o ../App/raw.o
TESTOBJS=example/test.o 

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) test

clean: 
	-rm *.o test example/*.o

test: $(TESTOBJS) $(OBJS) $(PACKETBUILDEROBJS)
	g++ $(TESTOBJS) $(OBJS) $(PACKETBUILDEROBJS) -o $@

ipv4.o: ipv4.cpp ipv4.h inetData.h ../packetBuffer.h ../encapsulateable.h \
  ../packetBuffer.h
test.o: test.cpp ipv4.h inetData.h ../packetBuffer.h ../encapsulateable.h \
  ../packetBuffer.h inet.h
inetData.o: inetData.h ../packetBuffer.h
inet.o: inet.h inetData.h ../packetBuffer.h ipv4.h ../encapsulateable.h \
  ../packetBuffer.h
ipv4.o: ipv4.h inetData.h ../packetBuffer.h ../encapsulateable.h \
  ../packetBuffer.h
