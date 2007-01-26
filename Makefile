# Makefile

CXX=g++
CC=g++

CXXFLAGS=-O2 -Wall -ansi -pedantic

.PHONY: all clean

all : graph

graph : graph.o

graph.o : graph.cpp *.hpp

clean :
	rm -f *.o *.exe graph *.stackdump *~

# EOF
