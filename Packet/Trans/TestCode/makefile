TRANSOBJS=../tcp.o ../udp.o ../tcpOptions.o ../trans.o
TESTTCPOBJS=../../packetBuffer.o testTcp.o
TESTUDPOBJS=../../packetBuffer.o testUdp.o
SCOPE=local
ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(TRANSOBJS) $(TESTTCPOBJS) $(TESTUDPOBJS)
else
	ALL=$(TRANSOBJS) $(TESTTCPOBJS) $(TESTUDPOBJS) testTcp testUdp
	CFLAGS=-ggdb -fPIC
endif
CXXFLAGS=$(CFLAGS)

all: $(ALL) 

clean: 
	-rm *.o testTcp testUdp ../*.o

testTcp:
	  g++ -ggdb $(TRANSOBJS) $(TESTTCPOBJS) -o $@

testUdp:
	  g++ -ggdb $(TRANSOBJS) $(TESTUDPOBJS) -o $@

