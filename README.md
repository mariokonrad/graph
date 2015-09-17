graph
=====

[![Build Status](https://travis-ci.org/mariokonrad/graph.svg?branch=master)](https://travis-ci.org/mariokonrad/graph)

Copyright (c) 2015 Mario Konrad (mario.konrad@gmx.net)


Abstract
--------

Small C++ library for graphs represented as adjecent matrix and related
algorithms.

Yes, there are already implementations for this, for example boost::graph.
This library is not only to have fun with the stuff, but also to have
solution with less dependencies.



Goals
-----

- small
- no unnecessary dependencies, except standard library
- unit tested



Features
--------

- Uni- and bidirectional graphs
- properties for nodes and edges
- algorithms:
  - shortest path (Dijkstras Algorithm)
  - mininum spanning tree (Prims Algorithm)
  - depth first search
  - breadth first search
  - topological sorting
  - rendering to dot (graphviz)



Examples
--------

Depth first search with printing the visited nodes:

~~~~~cpp
using namespace graph;

adjmatrix g{4, {{0, 1}, {0, 2}, {1, 2}, {2, 3}}};
depth_first_search(g, [](adjmatrix::vertex_t v) { std::cout << v << "\n"; });
~~~~~

Topological Sorting:

~~~~~cpp
using namespace graph;

adjmatrix g{4, {{0, 1}, {0, 2}, {1, 2}, {2, 3}}};
adjmatrix::vertex_list_t v;
bool has_cycle;
std::tie(v, has_cycle) = topological_sort(g);
~~~~~



Requirements
------------

This chapter describes the requirements in order to build the library.
Tools and their versions are listed below, newer/older/other tools
(i.e. compilers, etc.) may work, but not tested.

Compiler which supports C++14:
- GCC 4.9.2
- GCC 5.1.0
- Clang 3.6
- Clang 3.7

Tools needed to build the library:
- cmake 3.0

Tools needed to develop the library:
- git
- clang-format 3.7

Tools needed to build the documentation:
- doxygen
- graphviz

Optional used for development:
- lcov / genhtml, c++filt
- cppcheck
- clang-analyze (3.7 or newer)
- ctags, cscope



Build
-----

Build library (with examples) and test it:

~~~~~
mkdir build
cd build
cmake ..
make -j 8
make unittest
~~~~~

Build documentation:

~~~~~
mkdir build
cd build
cmake ..
make doc
~~~~~

Build for code coverage:

~~~~~
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make coverage
~~~~~



License
-------

See file [LICENSE](LICENSE)

(BSD)

	Copyright (c) 2015, Mario Konrad
	All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	   notice, this list of conditions and the following disclaimer in the
	   documentation and/or other materials provided with the distribution.
	3. All advertising materials mentioning features or use of this software
	   must display the following acknowledgement:
	   This product includes software developed by Mario Konrad.
	4. Neither the name of the software nor the names of its contributors
	   may be used to endorse or promote products derived from this software
	   without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
	AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
	FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
	DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
	SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
	CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
	OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
	OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


