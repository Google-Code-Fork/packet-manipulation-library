LINKDIR=Link
INETDIR=Inet
TRANSDIR=Trans
APPDIR=App
THIS=Packet

LAYERDIRS= $(LINKDIR) $(INETDIR) $(TRANSDIR) $(APPDIR)

OBJS=packetBuilder.o packetBuffer.o packet.o
TESTOBJS=example/test.o Link/ethernet.o Link/mac.o Link/link.o Inet/ipv4.o Inet/inet.o Trans/tcp.o Trans/tcpOptions.o Trans/udp.o Trans/trans.o App/raw.o App/app.o

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: subdir $(OBJS) test

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

test: $(OBJS) $(TESTOBJS)
	g++ $(OBJS) $(TESTOBJS) -o $@

packetBuffer.o: packetBuffer.cpp packetBuffer.h
packet.o: packet.cpp packet.h encapsulateable.h packetBuffer.h \
  Link/link.h Link/../encapsulateable.h Link/linkData.h \
  Link/../packetBuffer.h Link/ethernet.h Link/mac.h App/app.h \
  App/appData.h App/../packetBuffer.h App/../encapsulateable.h App/raw.h \
  Inet/inet.h Inet/inetData.h Inet/../packetBuffer.h \
  Inet/../encapsulateable.h Inet/ipv4.h Trans/trans.h Trans/transData.h \
  Trans/../packetBuffer.h Trans/../encapsulateable.h Trans/tcp.h \
  Trans/udp.h
test.o: test.cpp packetBuilder.h packet.h encapsulateable.h \
  packetBuffer.h Link/link.h Link/../encapsulateable.h Link/linkData.h \
  Link/../packetBuffer.h Link/ethernet.h Link/mac.h App/app.h \
  App/appData.h App/../packetBuffer.h App/../encapsulateable.h App/raw.h \
  Inet/inet.h Inet/inetData.h Inet/../packetBuffer.h \
  Inet/../encapsulateable.h Inet/ipv4.h Trans/trans.h Trans/transData.h \
  Trans/../packetBuffer.h Trans/../encapsulateable.h Trans/tcp.h \
  Trans/udp.h Link/ethernet.h Inet/ipv4.h Trans/tcp.h Trans/udp.h \
  App/raw.h
encapsulateable.o: encapsulateable.h packetBuffer.h
packetBuffer.o: packetBuffer.h
packetBuilder.o: packetBuilder.h packet.h encapsulateable.h \
  packetBuffer.h Link/link.h Link/../encapsulateable.h Link/linkData.h \
  Link/../packetBuffer.h Link/ethernet.h Link/mac.h App/app.h \
  App/appData.h App/../packetBuffer.h App/../encapsulateable.h App/raw.h \
  Inet/inet.h Inet/inetData.h Inet/../packetBuffer.h \
  Inet/../encapsulateable.h Inet/ipv4.h Trans/trans.h Trans/transData.h \
  Trans/../packetBuffer.h Trans/../encapsulateable.h Trans/tcp.h \
  Trans/udp.h Link/ethernet.h Inet/ipv4.h Trans/tcp.h Trans/udp.h \
  App/raw.h
packet.o: packet.h encapsulateable.h packetBuffer.h Link/link.h \
  Link/../encapsulateable.h Link/linkData.h Link/../packetBuffer.h \
  Link/ethernet.h Link/mac.h App/app.h App/appData.h \
  App/../packetBuffer.h App/../encapsulateable.h App/raw.h Inet/inet.h \
  Inet/inetData.h Inet/../packetBuffer.h Inet/../encapsulateable.h \
  Inet/ipv4.h Trans/trans.h Trans/transData.h Trans/../packetBuffer.h \
  Trans/../encapsulateable.h Trans/tcp.h Trans/udp.h
