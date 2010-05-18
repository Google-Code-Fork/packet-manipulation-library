OBJS=../inet.o ../ipv4.o ../icmp.o
PACKETBUILDEROBJS=../../packetBuilder.o ../../Link/ethernet.o ../../Link/mac.o ../../Link/link.o ../../Trans/udp.o ../../Trans/tcp.o ../../Trans/tcpOptions.o ../../Trans/trans.o ../../App/app.o ../../App/raw.o ../../packet.o
TESTIPV4OBJS=../../packetBuffer.o testIPv4.o
TESTICMPOBJS=../../packetBuffer.o testIcmp.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) testIPv4 testIcmp

clean: 
	-rm *.o testIPv4 testIcmp example/*.o

testIPv4: $(OBJS) $(TESTIPV4OBJS) $(PACKETBUILDEROBJS) 
	g++ -ggdb $(OBJS) $(TESTIPV4OBJS) $(PACKETBUILDEROBJS) -o $@

testIcmp: $(OBJS) $(TESTICMPOBJS) $(PACKETBUILDEROBJS)
	g++ -ggdb $(OBJS) $(TESTICMPOBJS) $(PACKETBUILDEROBJS) -o $@
