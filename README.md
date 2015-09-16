libgraph
========

Copyright (c) 2015 Mario Konrad (mario.konrad@gmx.net)


Abstract
--------

Small C++ library for graphs represented as adjecent matrix and related
algorithms.



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


