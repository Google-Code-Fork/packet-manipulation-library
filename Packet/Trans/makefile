include ../../global.mk

EXAMPLESOURCE=example/test.cpp ../packetBuffer.cpp
EXAMPLEOBJS=$(EXAMPLESOURCE:%.cpp=%.o)

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(TRANSOBJS) test 

clean: 
	-rm *.o test example/*.o

test: $(EXAMPLEOBJS) $(TRANSOBJS)
	g++ $(EXAMPLEOBJS) $(TRANSOBJS) -o $@

deps: $(TRANSSOURCE) $(TRANSHEADERS) $(EXAMPLESOURCE)
	g++ -MD -E $(TRANSSOURCE) $(TRANSHEADERS) $(EXAMPLESOURCE) > /dev/null

*.d: deps

include *.d
