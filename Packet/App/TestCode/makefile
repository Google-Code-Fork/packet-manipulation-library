OBJS=../raw.o
TESTRAWOBJS=../../packetBuffer.o testRaw.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) rawTest

clean:
	-rm *.o rawTest example/*.o

rawTest: $(OBJS) $(TESTRAWOBJS)
	g++ -ggdb $(OBJS) $(TESTRAWOBJS) -o $@

