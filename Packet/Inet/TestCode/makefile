OBJS=../inet.o ../ipv4.o ../icmp.o
TESTIPV4OBJS=../../packetBuffer.o testIPv4.o
TESTICMPOBJS=../../packetBuffer.o testIcmp.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) testIPv4 testIcmp

clean: 
	-rm *.o testIPv4 testIcmp example/*.o

testIPv4: $(OBJS) $(TESTIPV4OBJS) 
	g++ -ggdb $(OBJS) $(TESTIPV4OBJS) -o $@

testIcmp: $(OBJS) $(TESTICMPOBJS)
	g++ -ggdb $(OBJS) $(TESTICMPOBJS) -o $@
