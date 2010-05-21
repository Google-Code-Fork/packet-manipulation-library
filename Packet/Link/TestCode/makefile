include ../../../global.mk
LINKOBJS=../mac.o ../ethernet.o ../link.o
TESTETHEROBJS=../../packetBuffer.o ethernetTest.o
TESTMACOBJS=../../packetBuffer.o macTest.o
TESTSOURCE=../../packetBuffer.cpp ethernetTest.cpp macTest.cpp
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

testMac: 
	g++ -ggdb $(LINKOBJS) $(TESTMACOBJS) -o $@

testEthernet:
	g++ -ggdb $(LINKOBJS) $(TESTETHEROBJS) -o $@

deps: $(LINKSOURCE) $(TESTSOURCE)
	g++ -MD -E $(LINKSOURCE) $(TESTSOURCE) > /dev/null

*.d: deps

include *.d
