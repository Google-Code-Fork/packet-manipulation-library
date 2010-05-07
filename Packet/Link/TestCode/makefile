OBJS=../mac.o ../ethernet.o ../link.o
TESTETHEROBJS=../../packetBuffer.o ethernetTest.o
TESTMACOBJS=../../packetBuffer.o macTest.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) testEthernet testMac

clean: 
	-rm *.o testEthernet testMac example/*.o

testMac: $(OBJS) $(TESTMACOBJS) 
	g++ -ggdb $(OBJS) $(TESTMACOBJS) -o $@

testEthernet: $(OBJS) $(TESTETHEROBJS) 
	g++ -ggdb $(OBJS) $(TESTETHEROBJS) -o $@

