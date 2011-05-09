include ../../../global.mk
LINKOBJS=../mac.o ../ethernet.o ../link.o
TESTETHEROBJS=../../packetBuffer.o ethernetTest.o
TESTMACOBJS=../../packetBuffer.o macTest.o
TESTLINKOBJS=../../packetBuffer.o linkTest.o
TESTSOURCE=../../packetBuffer.cpp ethernetTest.cpp macTest.cpp linkTest.cpp
ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(LINKOBJS) $(TESTETHEROBJS) $(TESTMACOBJS) $(TESTLINKOBJS)
else
	ALL=$(LINKOBJS) $(TESTETHEROBJS) $(TESTMACOBJS) $(TESTLINKOBJS) testEthernet testMac testLink
	CFLAGS=-ggdb -fPIC
endif

CXXFLAGS=$(CFLAGS)

all: $(ALL) 

clean: 
	-rm *.o testEthernet testMac testLink 

testMac: $(LINKOBJS) $(TESTMACOBJS) 
	g++ -ggdb $(LINKOBJS) $(TESTMACOBJS) -o $@

testEthernet: $(LINKOBJS) $(TESTETHEROBJS)
	g++ -ggdb $(LINKOBJS) $(TESTETHEROBJS) -o $@

testLink: $(LINKOBJS) $(TESTLINKOBJS)
	g++ -ggdb $(LINKOBJS) $(TESTLINKOBJS) -o $@

deps: $(LINKSOURCE) $(TESTSOURCE)
	g++ -MD -E $(LINKSOURCE) $(TESTSOURCE) > /dev/null

*.d: deps

include *.d
