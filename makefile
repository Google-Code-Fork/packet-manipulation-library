PACKETDIR=Packet
DEVICEDIR=Device
SNIFFERDIR=Sniffer
INJECTORDIR=Injector
COMMONDIR=
MODULES = $(PACKETDIR) $(DEVICEDIR) $(SNIFFERDIR) $(INJECTORDIR) $(COMMONDIR) 

INSTALL_LIB=/usr/local/lib
INSTALL_INCLUDE=/usr/local/include/PacMan
all: pacman library

pacman:
	@echo
	@echo "****************************************"
	@echo "***     BUILDING ALL TARGETS         ***"
	@echo "****************************************"
	@echo 
	for i in $(MODULES) ; do \
	( cd $$i ; make ) ; \
	done

library:
	-mkdir lib
	-for i in $(MODULES) ; do \
	( cd $$i; cp *.o ../lib/ ) ; \
	done
	-mkdir include
	-for i in $(MODULES) ; do \
	( mkdir include/$$i; cd $$i; cp *.h ../include/$$i/ ) ; \
	done
	-( cd lib; ar rs libPacMan.a *.o; rm *.o ) ; 

packet:
	@cd $(PACKETDIR) ; make

clean: 
	 -rm -f *.o
	 -for i in $(MODULES) ; do \
	 ( cd $$i ; make clean) ; \
	 done
	 -cd Docs; make clean;
	 -cd Docs; rm refman.pdf;
	 -rm -rf lib
	 -rm -rf include

install: library
	cp lib/libPacMan.a $(INSTALL_LIB)
	cp -r include $(INSTALL_INCLUDE)

docs: 
	doxygen
	cd Docs/latex; make pdf;
	mv Docs/latex/refman.pdf Docs/;
