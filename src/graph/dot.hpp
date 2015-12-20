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
/// \cond DEV
namespace detail
{
template <class T> struct DefaultPropertyMapAccess {
	std::string operator()(const T &) const { return {}; }
};
}
/// \endcond

/// \brief Renders the specified graph to a string in the Dot (graphviz) format.
///
/// \todo SFINAE for property accessors
///
/// \tparam Graph Type of the graph to render
/// \tparam VertexPropertyAccess Accessor for vertex properties
/// \tparam EdgePropertyAccess Accessor for edge properties
///
/// \param[in] g The graph to render
/// \param[in] graph_prop Properties for the graph in general
/// \param[in] node_prop Default properties for all nodes
/// \param[in] edge_prop Default properties for all edges
/// \param[in] vp Vertex property accessor
/// \param[in] ep Edge property accessor
/// \return The string, representing the graph in the Dot language
///
template <class Graph, class VertexPropertyAccess = detail::DefaultPropertyMapAccess<vertex>,
	class EdgePropertyAccess = detail::DefaultPropertyMapAccess<edge>,
	typename = typename std::enable_if<detail::has_f_vertices<Graph>::value
			&& detail::has_f_edges<Graph>::value,
		void>::type>
std::string dot(const Graph & g, const std::string & graph_prop = "",
	const std::string & node_prop = "", const std::string edge_prop = "",
	VertexPropertyAccess vp = VertexPropertyAccess{},
	EdgePropertyAccess ep = EdgePropertyAccess{})
{
	std::ostringstream s;

	s << "digraph G {\n";
	if (!graph_prop.empty())
		s << "\t" << graph_prop << ";\n";
	if (!node_prop.empty())
		s << "\tnode [" << node_prop << "];\n";
	if (!edge_prop.empty())
		s << "\tedge [" << edge_prop << "];\n";
	for (auto const & v : g.vertices()) {
		s << "\t" << v;
		auto property = vp(v);
		if (!property.empty())
			s << " [" << property << "]";
		s << ";\n";
	}
	for (auto const & e : g.edges()) {
		s << "\t" << e.from << " -> " << e.to;
		auto property = ep(e);
		if (!property.empty())
			s << " [" << property << "]";
		s << ";\n";
	}
	s << "}\n";

	return s.str();
}
}

#endif
