OBJS=../tcp.o ../udp.o
TESTTCPOBJS=../../packetBuffer.o testTcp.o
TESTUDPOBJS=../../packetBuffer.o testUdp.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) testTcp testUdp

clean: 
	-rm *.o testTcp testUdp example/*.o

testTcp: $(OBJS) $(TESTTCPOBJS)
	  g++ -ggdb $(OBJS) $(TESTTCPOBJS) -o $@

testUdp: $(OBJS) $(TESTUDPOBJS)
	  g++ -ggdb $(OBJS) $(TESTUDPOBJS) -o $@

