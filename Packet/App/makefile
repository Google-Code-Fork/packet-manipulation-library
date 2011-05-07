include ../../global.mk

EXAMPLESOURCE=exampleCode/test.cpp ../packetBuffer.cpp
EXAMPLEOBJS=$(EXAMPLESOURCE:%.cpp=%.o)
COMMONOBJS=../../common/stringUtils.o

CFLAGS=-ggdb -fPIC
CXXFLAGS=$(CFLAGS)

all: $(APPOBJS) $(COMMONOBJS) example 

clean: 
	-rm *.o test exampleCode/*.o *.d example

example: $(EXAMPLEOBJS) $(APPOBJS)
	g++ $(EXAMPLEOBJS) $(APPOBJS) $(COMMONOBJS) -o $@

deps: $(APPSOURCE) $(APPHEADERS) $(EXAMPLESOURCE)
	g++ -MD -E $(APPSOURCE) $(EXAMPLESOURCE) > /dev/null

*.d: deps

include *.d
