.PHONY: all clean tags dependencies

CXX=g++
CXXFLAGS=-std=c++11 -O0 -Wall -Wextra -pedantic -ggdb

all : graph

tags :
	find . -type f -regextype posix-egrep -regex ".*\.(cpp|cc|cxx|c|hpp|hh|hxx|h)" > cscope.files
	ctags -L cscope.files
	cscope -b

graph : graph.o
	$(CXX) $(CXXFLAGS) -o $@ $^

-include $(wildcard *.d)

clean :
	rm -f *.o *.d
	rm -f tags cscope.files cscope.out
	rm -f graph

dependencies :
	$(CXX) $(CXXFLAGS) -MM *.cpp

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	@$(CXX) $(CXXFLAGS) -MM $< > $<.d


