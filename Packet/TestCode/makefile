include ../../global.mk

TESTPACKETOBJS=testPacket.o

ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(LINKOBJS) $(TESTETHEROBJS) $(TESTMACOBJS) 
else
	ALL=$(LINKOBJS) $(TESTETHEROBJS) $(TESTMACOBJS) testEthernet testMac
	CFLAGS=-ggdb -fPIC
endif

CXXFLAGS=$(CFLAGS)

all: $(ALL) 

clean: 
	-rm *.o testEthernet testMac example/*.o

testPacket: 
	g++ -ggdb $(LINKOBJS) $(TESTPACKETOBJS) -o $@

