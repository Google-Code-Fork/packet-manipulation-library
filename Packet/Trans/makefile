include ../../global.mk

EXAMPLESOURCE=exampleCode/test.cpp ../packetBuffer.cpp
EXAMPLEOBJS=$(EXAMPLESOURCE:%.cpp=%.o)

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(TRANSOBJS) example 

clean: 
	-rm *.o example exampleCode/*.o *.d 

example: $(EXAMPLEOBJS) $(TRANSOBJS)
	g++ $(EXAMPLEOBJS) $(TRANSOBJS) -o $@

deps: $(TRANSSOURCE) $(TRANSHEADERS) $(EXAMPLESOURCE)
	g++ -MD -E $(TRANSSOURCE) $(TRANSHEADERS) $(EXAMPLESOURCE) > /dev/null

*.d: deps

include *.d
