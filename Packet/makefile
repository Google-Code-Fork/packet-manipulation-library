LINKDIR=Link
INETDIR=Inet
TRANSDIR=Trans
APPDIR=App

LAYERDIRS= $(LINKDIR) $(INETDIR) $(TRANSDIR) $(APPDIR)

OBJS=packetBuffer.o packet.o

all: $(OBJS)
	@echo
	@echo "**************************************"
	@echo "***  BUILDING ALL PACKET STUFF     ***"
	@echo "**************************************"
	@echo
	for i in $(LAYERDIRS) ; do \
	( cd $$i ; make ) ; \
	done

clean:
	 -rm -f *.o
	 for i in $(LAYERDIRS) ; do \
	 ( cd $$i ; make clean ) ; \
	 done
