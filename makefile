PACKETDIR=Packet
SNIFFERDIR=sniffer
INJECTORDIR=Injector
COMMONDIR=
MODULES = $(PACKETDIR) $(SNIFFERDIR) $(INJECTORDIR) $(COMMONDIR) 

all:
	@echo
	@echo "****************************************"
	@echo "***     BUILDING ALL TARGETS         ***"
	@echo "****************************************"
	@echo 
	for i in $(MODULES) ; do \
	( cd $$i ; make ) ; \
	done

packet:
	@cd $(PACKETDIR) ; make

clean: 
	 -rm -f *.o
	 for i in $(MODULES) ; do \
	 ( cd $$i ; make clean) ; \
	 done
	 cd Docs; make clean;

docs: 
	doxygen
	cd Docs/latex; make pdf;
	mv Docs/latex/refman.pdf Docs/;
