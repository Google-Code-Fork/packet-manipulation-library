OBJS=mac.o ethernet.o link.o
EXAMPLEOBJS=../packetBuffer.o exampleCode/test.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) example

clean: 
	-rm *.o example example/*.o

example: $(OBJS) $(EXAMPLEOBJS) 
	g++ -ggdb $(OBJS) $(EXAMPLEOBJS) -o example


ethernet.o: ethernet.cpp ethernet.h mac.h linkData.h ../packetBuffer.h
mac.o: mac.cpp mac.h linkData.h ../packetBuffer.h
test.o: test.cpp ethernet.h mac.h linkData.h ../packetBuffer.h
ethernet.o: ethernet.h mac.h linkData.h ../packetBuffer.h
linkData.o: linkData.h ../packetBuffer.h
link.o: link.h linkData.h ../packetBuffer.h ethernet.h mac.h
mac.o: mac.h linkData.h ../packetBuffer.h
