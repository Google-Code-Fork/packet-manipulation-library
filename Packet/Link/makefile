include ../../global.mk

EXAMPLESOURCE=../packetBuffer.cpp exampleCode/test.cpp
EXAMPLEOBJS=$(EXAMPLESOURCE:%.cpp=%.o)

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(LINKOBJS) example

clean: 
	-rm *.o example exampleCode/*.o *.d

example: $(LINKOBJS) $(EXAMPLEOBJS) 
	g++ -ggdb $(LINKOBJS) $(EXAMPLEOBJS) -o example

deps: $(LINKSOURCE) $(LINKHEADERS) $(EXAMPLESOURCE)
	g++ -MD -E $(LINKSOURCE) $(EXAMPLESOURCE) > /dev/null

*.d: deps

include *.d
