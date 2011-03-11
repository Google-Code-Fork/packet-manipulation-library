include ../../global.mk

EXAMPLESOURCE=exampleCode/test.cpp ../packetBuffer.cpp
EXAMPLEOBJS=$(EXAMPLESOURCE:%.cpp=%.o)

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(APPOBJS) example 

clean: 
	-rm *.o test exampleCode/*.o *.d

example: $(EXAMPLEOBJS) $(APPOBJS)
	g++ $(EXAMPLEOBJS) $(APPOBJS) -o $@

deps: $(APPSOURCE) $(APPHEADERS) $(EXAMPLESOURCE)
	g++ -MD -E $(APPSOURCE) $(EXAMPLESOURCE) > /dev/null

*.d: deps

include *.d
