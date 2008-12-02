OBJS=mac.o ethernet.o
TESTOBJS=../packetBuffer.o

all: $(OBJS) test

clean: 
	-rm *.o

test: $(OBJS) $(TESTOBJS) test.cpp
	g++ -ggdb test.cpp $(OBJS) $(TESTOBJS) -o test


ethernet.o: ethernet.cpp ethernet.h mac.h linkData.h ../packetBuffer.h
mac.o: mac.cpp mac.h linkData.h ../packetBuffer.h
test.o: test.cpp ethernet.h mac.h linkData.h ../packetBuffer.h
ethernet.o: ethernet.h mac.h linkData.h ../packetBuffer.h
linkData.o: linkData.h ../packetBuffer.h
link.o: link.h linkData.h ../packetBuffer.h ethernet.h mac.h
mac.o: mac.h linkData.h ../packetBuffer.h
