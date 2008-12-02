OBJS=raw.o
TESTOBJS=test.o ../packetBuffer.o

CFLAGS=-ggdb
CXXFLAGS=$(CFLAGS)

all: $(OBJS) test

clean: 
	-rm *.o

test: $(TESTOBJS) $(OBJS)
	g++ $(TESTOBJS) $(OBJS) -o $@

raw.o: raw.cpp raw.h appData.h ../packetBuffer.h
test.o: test.cpp raw.h appData.h ../packetBuffer.h app.h
appData.o: appData.h ../packetBuffer.h
app.o: app.h appData.h ../packetBuffer.h raw.h
raw.o: raw.h appData.h ../packetBuffer.h
