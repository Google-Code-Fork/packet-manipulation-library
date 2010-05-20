include ../../global.mk

EXAMPLESOURCE=exampleCode/test.cpp
EXAMPLEOBJS=$(EXAMPLESOURCE:%.cpp=%.o)

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: deps $(INETOBJS) example 

clean: 
	-rm *.o example exampleCode/*.o *.d 

example: $(EXAMPLEOBJS) $(PACKETOBJS)
	g++ $(EXAMPLEOBJS) $(PACKETOBJS) -o $@

deps: $(PACKETSOURCE) $(PACKETHEADER) $(EXAMPLESOURCE)
	g++ -MD -E $(PACKETSOURCE) $(PACKETHEADER) $(EXAMPLESOURCE) > /dev/null

*.d: deps


include *.d
