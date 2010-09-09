include ../../../global.mk
TESTIPV4OBJS=testIPv4.o
TESTICMPOBJS=testIcmp.o
TESTIPV6OBJS=testIPv6.o
SCOPE=local
ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(TESTIPV4OBJS) $(TESTICMPOBJS) $(PACKETOBJS) $(TESTIPV6OBJS)
else
	ALL=$(TESTIPV4OBJS) $(TESTICMPOBJS) $(PACKETOBJS) $(TESTIPV6OBJS) testIPv4 testIcmp testIPv6
	CFLAGS=-ggdb -fPIC
endif

CXXFLAGS=$(CFLAGS)
	

all: $(ALL) 

clean: 
	-rm *.o testIPv4 testIcmp testIPv6 ../*.o

testIPv4: $(TESTIPV4OBJS) $(PACKETOBJS)
	g++ -ggdb $(TESTIPV4OBJS) $(PACKETOBJS) -o $@

testIcmp: $(TESTICMPOBJS) $(PACKETOBJS)
	g++ -ggdb $(TESTICMPOBJS) $(PACKETOBJS) -o $@

testIPv6: $(TESTIPV6OBJS) $(PACKETOBJS)
	g++ -ggdb $(TESTIPV6OBJS) $(PACKETOBJS) -o $@
