// License: BSD
//
// Copyright (c) 2015, Mario Konrad
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this software
//    must display the following acknowledgement:
//    This product includes software developed by Mario Konrad.
// 4. Neither the content of this file nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef __GRAPH__DOT_PRINT__HPP__
#define __GRAPH__DOT_PRINT__HPP__

#include <string>
#include <sstream>
#include <graph/type_traits.hpp>
#include <graph/edge.hpp>

namespace graph
{
/// Renders the specified graph to a string in the Dot (graphviz)
/// format.
///
/// \todo Extend parameters to support property map for vertices
/// \todo Extend parameters to support property map for edges
///
/// \param[in] g The graph to render
/// \return The string, representing the graph in the Dot language
template <class Graph, typename = typename std::enable_if<detail::has_f_vertices<Graph>::value
							   && detail::has_f_edges<Graph>::value,
						   void>::type>
std::string dot(const Graph & g)
{
	std::ostringstream s;

	s << "digraph G {\n";
	s << "\tnode [shape=circle];\n";
	for (auto const & v : g.vertices()) {
		s << "\t" << v << ";\n";
	}
	for (auto const & e : g.edges()) {
		s << "\t" << e.from << " -> " << e.to << ";\n";
	}
	s << "}\n";

	return s.str();
}
}

#endif
