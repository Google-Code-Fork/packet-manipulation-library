include ../../../global.mk
TESTIPV4OBJS=testIPv4.o
TESTICMPOBJS=testIcmp.o
SCOPE=local
ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(TESTIPV4OBJS) $(TESTICMPOBJS) $(PACKETOBJS)
else
	ALL=$(TESTIPV4OBJS) $(TESTICMPOBJS) $(PACKETOBJS) testIPv4 testIcmp
	CFLAGS=-ggdb -fPIC
endif

CXXFLAGS=$(CFLAGS)
	

all: $(ALL) 

clean: 
	-rm *.o testIPv4 testIcmp ../*.o

testIPv4: $(TESTIPV4OBJS) $(PACKETOBJS)
	g++ -ggdb $(TESTIPV4OBJS) $(PACKETOBJS) -o $@

testIcmp: $(TESTICMPOBJS) $(PACKETOBJS)
	g++ -ggdb $(TESTICMPOBJS) $(PACKETOBJS) -o $@
