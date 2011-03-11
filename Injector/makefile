include ../global.mk

OBJS=injector.o
TESTOBJS=example/test.o 
DEVICEOBJS=../Device/device.o ../Device/devicesLookup.o
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)
LDFLAGS=-lpcap
THIS=Injector

all: $(OBJS)  test

clean:
	 -rm -f *.o test example/*.o

lib:
	cp *.o ../lib/

include:
	-mkdir ../include/$(THIS)
	-cp *.h ../include/$(THIS)

test: $(OBJS) $(TESTOBJS) $(PACKETOBJS) $(DEVICEOBJS)
	g++ $(LDFLAGS) $(OBJS) $(TESTOBJS) $(PACKETOBJS) $(DEVICEOBJS) -o $@
