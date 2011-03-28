APPOBJS=../raw.o ../arp.o
TESTRAWOBJS=../../packetBuffer.o testRaw.o 
TESTARPOBJS=../../packetBuffer.o testArp.o
SCOPE=local

ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(APPOBJS) $(TESTRAWOBJS)
else
	CFLAGS=-ggdb -fPIC 
	ALL=$(APPOBJS) $(TESTRAWOBJS) testRaw testArp
endif
	
CXXFLAGS=$(CFLAGS)

all: $(ALL)

clean:
	-rm *.o testRaw ../*.o

testRaw: $(APPOBJS) $(TESTRAWOBJS)
	g++ -ggdb $(APPOBJS) $(TESTRAWOBJS) -o $@

testArp: $(APPOBJS) $(TESTARPOBJS) 
	g++ --ggdb $(APPOBJS) $(TESTARPOBJS) -o $@
