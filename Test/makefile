include ../global.mk

LAYERTESTDIRS= $(LINKTESTDIR) $(INETTESTDIR) $(TRANSTESTDIR) $(APPTESTDIR)

TESTOBJS=$(LINKTESTOBJS) $(INETTESTOBJS) $(TRANSTESTOBJS) $(APPTESTOBJS)
OBJS=main.o
CFLAGS=-ggdb -fPIC -D GLOBAL_SCOPE
CXXFLAGS=$(CFLAGS)

all: subdir $(OBJS) test

include: 
	-mkdir ../include/$(THIS)
	-for i in $(LAYERTESTDIRS) ; do \
	( mkdir ../include/$(THIS)/$$i ) ; \
	done
	-for i in $(LAYERTESTDIRS) ; do \
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
	@echo "***   BUILDING ALL PACKET TESTS    ***"
	@echo "**************************************"
	@echo
	for i in $(LAYERTESTDIRS) ; do \
	( cd $$i ; make SCOPE=global ) ; \
	done

clean:
	 -rm -f *.o test
	 for i in $(LAYERTESTDIRS) ; do \
	 ( cd $$i ; make clean ) ; \
	 done
	 

test: $(OBJS) $(TESTOBJS) $(PACKETOBJS)
	g++ $(OBJS) $(TESTOBJS) $(PACKETOBJS) -o $@

