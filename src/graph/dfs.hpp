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

#ifndef GRAPH__DFS__HPP
#define GRAPH__DFS__HPP

#include <graph/type_traits.hpp>
#include <graph/edge.hpp>

namespace graph
{
/// \cond DEV
namespace detail
{
template <class Graph, class Visitor>
static void recursive_dfs(
	const Graph & g, vertex id, Visitor & visitor, visited_vertex_list & visited)
{
	// guard
	if (id >= g.size())
		return;
	if (visited[id])
		return;

	// visit
	visited[id] = true;
	visitor(g, id);

	// search deeper
	for (vertex i = 0; i < g.size(); ++i)
		if ((i != id) && g.at({id, i}))
			recursive_dfs(g, i, visitor, visited);
}
}
/// \endcond

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'depth first'.
///
/// \tparam Graph The graph type.
///   Must provide the following features:
///   - function `size_type size() const` which returns the number of nodes in the graph
///   - function `integral_type at(edge) const` which returns the status of the specified edge.
///     integral types can implictly converted to `bool`, which is in fact a hard
///     requirement.
/// \tparam Visitor The visitor type. Must provide the ability to get called
///   with a signature like `(Graph, vertex)`, e.g. `void visitor(const Graph &, vertex v)`.
///
/// \param[in] g The graph to visit.
/// \param[in] v The starting vertex.
/// \param[in] visitor Visitor which gets called for each found vertex.
/// \return The visitor functor
///
template <class Graph, class Visitor,
	typename = typename std::enable_if<detail::has_t_size_type<Graph>::value
			&& detail::has_f_size<Graph>::value && detail::has_f_integral_type_at<Graph>::value,
		void>::type>
Visitor depth_first_search(const Graph & g, vertex v, Visitor visitor)
{
	visited_vertex_list visited(g.size(), false);
	detail::recursive_dfs(g, v, visitor, visited);
	return visitor;
}
}

#endif
