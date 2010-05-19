OBJS=../raw.o
TESTRAWOBJS=../../packetBuffer.o testRaw.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) testRaw

clean:
	-rm *.o rawTest example/*.o

testRaw: $(OBJS) $(TESTRAWOBJS)
	g++ -ggdb $(OBJS) $(TESTRAWOBJS) -o $@

