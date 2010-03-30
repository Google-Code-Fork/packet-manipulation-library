OBJS=../packetfingerprint.o ../signatures.o ../../Packet/Trans/tcpOptions.o
TESTOBJS=test.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lpcap
THIS=Classifier

test: $(OBJS) $(TESTOBJS)
	g++ -o $@ $(OBJS) $(TESTOBJS)

include:
	-mkdir ../include/$(THIS)
	-cp *.h ../include/$(THIS)

lib:
	cp *.o ../lib/

clean:
	 -rm -f *.o
