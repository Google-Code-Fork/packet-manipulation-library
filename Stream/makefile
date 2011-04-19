include ../global.mk
INCLUDE=
OBJS=tcpStream.o
CFLAGS=-ggdb $(INCLUDE) -fPIC
CXXFLAGS=$(CFLAGS) 
THIS=Stream

all: $(OBJS) 

clean:
	-rm -f *.o 

include:
	-mkdir ../include/$(THIS)
	-cp *.h ../include/$(THIS)

lib:
	cp *.o ../lib

PCAPLINK=-L/usr/lib/  
LDFLAGS=$(PCAPLINK) -lpthread -lpcap

