#MAKEFILE FOR INAV SERVER

#Select your platform (hack to get compilation under BSD, we'll use autotools in the future)
PLATFORM=LINUX
#PLATFORM=BSD

#modify this for where your libpcap files are
PCAPLIBS=-I/usr/lib/ -I/usr/include  
PCAPLINK=-L/usr/lib/  
  
NEWOBJS=dataQueue.o
OBJS= clientComm.o clientCommData.o baseData.o snifferData.o sniffer.o ethernet.o ip.o tcp.o packet.o filterData.o graphData.o bandwidthMonitor.o ../common/semaphore.o icmp.o traceroute/tracerouteData.o traceroute/tracerouteThread.o ../common/commandLineParser.o ../common/xmlParser.o ../common/helper.o udp.o ../common/parseCommas.o debugThread.o ../common/mutex.o ../common/threads.o $(NEWOBJS)
TESTOBJS=$(OBJS) tester.o 
SERVOBJS=$(OBJS) inavServer.o
CC=g++
CXXFLAGS=-ggdb -g3 -D $(PLATFORM) -D INAV_VERSION=$(VERSION) $(PCAPLIBS)
OPTOMIZE=-O2 -funroll-loops -fprefetch-loop-arrays 
LDFLAGS=$(PCAPLINK) -lpthread -lpcap
LDTESTFLAGS= $(LDFLAGS) -ldl -lcppunit
DEPEND= makedepend $(CFLAGS)
	
VERSION=$(shell ./version.sh)

inavd: $(SERVOBJS)
	$(CC) $(LDFLAGS) -o $@ $(SERVOBJS)

update: removeBuild removeMinorVersion svnUpdate inavd

all: unitTest inavd 

unitTest: $(TESTOBJS)
	$(CC) $(LDTESTFLAGS) -o $@ $(TESTOBJS)

svnUpdate:
	svn update

removeBuild:
	-rm build.txt

removeMinorVersion:
	-rm minorVersion.txt

build: increaseBuild $(SERVOBJS) inavd

increaseBuild:
	-rm inavServer.o
	./version.sh -b

increaseVersion:
	-rm inavServer.o
	./version.sh -r 

release: increaseVersion $(SERVOBJS) inavd

clean:
	-rm *.o ../common/*.o inavd unitTest inavd.log traceroute/*.o
