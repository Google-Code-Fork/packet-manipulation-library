OBJS=../inet.o ../ipv4.o
TESTIPV4OBJS=../../packetBuffer.o testIPv4.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(OBJS) testIPv4

clean: 
	-rm *.o testIPv4 example/*.o

testIPv4: $(OBJS) $(TESTIPV4OBJS) 
	g++ -ggdb $(OBJS) $(TESTIPV4OBJS) -o $@

