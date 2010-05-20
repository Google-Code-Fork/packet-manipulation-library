APPOBJS=../raw.o
TESTRAWOBJS=../../packetBuffer.o testRaw.o
SCOPE=local

ifeq ($(SCOPE),global)
	CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
	ALL=$(APPOBJS) $(TESTRAWOBJS)
else
	CFLAGS=-ggdb -fPIC 
	ALL=$(APPOBJS) $(TESTRAWOBJS) testRaw
endif
	
CXXFLAGS=$(CFLAGS)

all: $(ALL)

clean:
	-rm *.o testRaw ../*.o

testRaw: $(APPOBJS) $(TESTRAWOBJS)
	g++ -ggdb $(APPOBJS) $(TESTRAWOBJS) -o $@

