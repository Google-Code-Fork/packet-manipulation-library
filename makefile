PACKETDIR=Packet
DEVICEDIR=Device
SNIFFERDIR=Sniffer
INJECTORDIR=Injector
COMMONDIR=common
FINGERPRINT=FingerPrint
MODULES = $(PACKETDIR) $(DEVICEDIR) $(SNIFFERDIR) $(INJECTORDIR) $(COMMONDIR) $(FINGERPRINT)

INSTALL_LIB=/usr/lib/
INSTALL_INCLUDE=/usr/local/include/PacMan/
all: pacman lib

pacman:
	@echo
	@echo "****************************************"
	@echo "***     BUILDING ALL TARGETS         ***"
	@echo "****************************************"
	@echo 
	for i in $(MODULES) ; do \
	( cd $$i ; make ) ; \
	done

lib: pacman
	-mkdir lib
	-for i in $(MODULES) ; do \
	( cd $$i; make lib ) ; \
	done
	-mkdir include
	-for i in $(MODULES) ; do \
	( cd $$i; make include ) ; \
	done
	-( cd lib; g++ -lpcap -shared -o libpacman.so *.o; rm *.o ) ; 
#	-( cd lib; g++ -shared -o libpacman.so *.o; rm *.o ) ; 

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

install: 
	cp lib/libpacman.so $(INSTALL_LIB)
	-mkdir $(INSTALL_INCLUDE)
	cp -r include/* $(INSTALL_INCLUDE)

docs: 
	doxygen
	cd Docs/latex; make pdf;
	mv Docs/latex/refman.pdf Docs/;
