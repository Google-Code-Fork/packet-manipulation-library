OBJS=packetfingerprint.o signatures.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lpcap
THIS=FingerPrinter

all: $(OBJS) 

include:
	-mkdir ../include/$(THIS)
	-cp *.h ../include/$(THIS)

lib:
	cp *.o ../lib/

clean:
	 -rm -f *.o
