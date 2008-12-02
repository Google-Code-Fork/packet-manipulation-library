OBJS=tcp.o udp.o trans.o
TESTOBJS=test.o ../packetBuffer.o

CFLAGS=-ggdb
CXXFLAGS=$(CFLAGS)

all: $(OBJS) test

clean: 
	-rm *.o

test: $(TESTOBJS) $(OBJS)
	g++ $(TESTOBJS) $(OBJS) -o $@


tcp.o: tcp.cpp tcp.h transData.h ../packetBuffer.h
udp.o: udp.cpp udp.h transData.h ../packetBuffer.h
tcp.o: tcp.h transData.h ../packetBuffer.h
transData.o: transData.h ../packetBuffer.h
udp.o: udp.h transData.h ../packetBuffer.h
tcp.o: tcp.cpp tcp.h transData.h ../packetBuffer.h
test.o: test.cpp tcp.h transData.h ../packetBuffer.h udp.h trans.h
udp.o: udp.cpp udp.h transData.h ../packetBuffer.h
tcp.o: tcp.h transData.h ../packetBuffer.h
transData.o: transData.h ../packetBuffer.h
trans.o: trans.h transData.h ../packetBuffer.h tcp.h udp.h
udp.o: udp.h transData.h ../packetBuffer.h
