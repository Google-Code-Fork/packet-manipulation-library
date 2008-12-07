OBJS=ipv4.o inet.o
TESTOBJS=test.o ../packetBuffer.o

CFLAGS=-ggdb
CXXFLAGS=$(CFLAGS)

all: $(OBJS) test

clean: 
	-rm *.o test

test: $(TESTOBJS) $(OBJS)
	g++ $(TESTOBJS) $(OBJS) -o $@

ipv4.o: ipv4.cpp ipv4.h inetData.h ../packetBuffer.h ../encapsulateable.h \
  ../packetBuffer.h
test.o: test.cpp ipv4.h inetData.h ../packetBuffer.h ../encapsulateable.h \
  ../packetBuffer.h inet.h
inetData.o: inetData.h ../packetBuffer.h
inet.o: inet.h inetData.h ../packetBuffer.h ipv4.h ../encapsulateable.h \
  ../packetBuffer.h
ipv4.o: ipv4.h inetData.h ../packetBuffer.h ../encapsulateable.h \
  ../packetBuffer.h
