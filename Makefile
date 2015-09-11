.PHONY: all clean tags

CXX=g++
CXXFLAGS=-std=c++11 -O0 -Wall -Wextra -pedantic -ggdb

all : graph

tags :
	find . -type f -regextype posix-egrep -regex ".*\.(cpp|cc|cxx|c|hpp|hh|hxx|h)" > cscope.files
	ctags -L cscope.files
	cscope -b

graph : graph.o
	$(CXX) $(CXXFLAGS) -o $@ $^

clean :
	rm -f *.o *.exe *.stackdump *~
	rm -f tags cscope.files cscope.out
	rm -f graph

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

