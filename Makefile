# Makefile

CXX=g++
CC=g++

.PHONY: all clean

all : graph

graph : graph.o

graph.o : graph.cpp *.hpp

clean :
	rm -f *.o *.exe graph *.stackdump *~

# EOF
