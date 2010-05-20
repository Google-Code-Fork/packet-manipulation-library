include ../global.mk
THIS=Packet
EXAMPLEDIR=exampleCode
LAYERDIRS= $(LINKDIR) $(INETDIR) $(TRANSDIR) $(APPDIR)

OBJS=packetBuilder.o packetBuffer.o packet.o
EXAMPLEOBJS=exampleCode/test.o Link/ethernet.o Link/mac.o Link/link.o Inet/ipv4.o Inet/inet.o Trans/tcp.o Trans/tcpOptions.o Trans/udp.o Trans/trans.o App/raw.o App/app.o Inet/icmp.o
EXAMPLESOURCE=$(EXAMPLEOBJS:%.o=%.cpp)
CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: subdir $(OBJS) example 

include: 
	-mkdir ../include/$(THIS)
	-for i in $(LAYERDIRS) ; do \
	( mkdir ../include/$(THIS)/$$i ) ; \
	done
	-for i in $(LAYERDIRS) ; do \
	( cd $$i ; cp *.h ../../include/$(THIS)/$$i/ ) ; \
	done
	-cp *.h ../include/$(THIS)

lib: subdir $(OBJS)
	for i in $(LAYERDIRS) ; do \
	( cd $$i ; cp *.o ../../lib/ ) ; \
	done
	cp *.o ../lib

subdir:
	@echo
	@echo "**************************************"
	@echo "***  BUILDING ALL PACKET STUFF     ***"
	@echo "**************************************"
	@echo
	for i in $(LAYERDIRS) ; do \
	( cd $$i ; make ) ; \
	done

clean:
	 -rm -f *.o test
	 for i in $(LAYERDIRS) ; do \
	 ( cd $$i ; make clean ) ; \
	 done
	 cd $(EXAMPLEDIR) ; rm -f *.o

example: $(OBJS) $(EXAMPLEOBJS)
	g++ $(OBJS) $(EXAMPLEOBJS) -o $@

deps: $(EXAMPLESOURCE) $(PACKETSOURCE)
	g++ -MD -E $(PACKETSOURCE) $(EXAMPLESOURCE) > /dev/null

*.d: deps

include *.d
