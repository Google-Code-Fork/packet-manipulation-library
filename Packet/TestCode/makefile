include ../../global.mk

TESTPACKETOBJS=packetTest.o ../packetBuffer.o ../packet.o ../packetBuilder.o ../../common/stringUtils.o

ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(LINKOBJS) $(TESTETHEROBJS) $(TESTMACOBJS) 
else
	ALL=$(LINKOBJS) $(TESTETHEROBJS) $(TESTMACOBJS) testPacket
	CFLAGS=-ggdb -fPIC
endif

CXXFLAGS=$(CFLAGS)

all: $(ALL) 

clean: 
	-rm *.o testEthernet testMac example/*.o

testPacket: $(TESTPACKETOBJS) $(LINKOBJS) $(INETOBJS) $(TRANSOBJS) $(APPOBJS) 
	g++ -ggdb $(LINKOBJS) $(INETOBJS) $(TRANSOBJS) $(APPOBJS) $(TESTPACKETOBJS) -o $@

