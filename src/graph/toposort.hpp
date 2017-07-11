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

#ifndef GRAPH__TOPOSORT__HPP
#define GRAPH__TOPOSORT__HPP

#include <tuple>
#include <graph/type_traits.hpp>
#include <graph/edge.hpp>

namespace graph
{
/// This algorithm adds the vertices of the specified matrix
/// to the vertex list in topological order. The graph must
/// be free of cycles to determine a topological order.
///
/// Complexity: O(V + E)
///
/// \tparam Graph The graph type to visit.
///   Must provide the following features:
///   - copy constructible
///   - type 'size_type'
///   - function `size_type size() const` which returns the number of nodes in the graph
///   - function `bool at(edge) const` which returns the status of the specified edge.
///   - function `void remove(edge)` which removes an edge from the graph
///   - function `size_type count_incoming(vertex) const` which returns the number of incoming
///     edges for a node
///   - function `size_type count_edges() const` which returns the number of edges within the
///   graph
///
/// \param[in] g The adjacency matrix.
/// \return A tuple containing the list and a status which is:
///   - \c true : sorting successful
///   - \c false : graph contains cycles
///
template <class Graph, typename = typename std::enable_if<detail::has_t_size_type<Graph>::value
							   && detail::has_f_remove<Graph>::value
							   && detail::has_f_integral_type_at<Graph>::value
							   && detail::has_f_count_incoming<Graph>::value
							   && detail::has_f_count_edges<Graph>::value,
						   void>::type>
std::tuple<vertex_list, bool> topological_sort(const Graph & g)
{
	// copy of matrix to work on (remove edges)
	Graph tm(g);

	// all nodes with no incoming edges
	vertex_list Q;
	for (vertex i = 0; i < g.size(); ++i)
		if (tm.count_incoming(i) == 0)
			Q.push_back(i);

	vertex_list v;

	// sort
	while (Q.size() > 0) {
		// remove node from Q
		vertex node = Q.front();
		Q.erase(Q.begin());

		// node is member of the result vector
		v.push_back(node);

		for (vertex i = 0; i < tm.size(); ++i) {
			if (i == node)
				continue; // not to self
			if (tm.at({node, i})) {
				tm.remove({node, i}); // remove edge from graph

				// has i other incoming edges?
				if (tm.count_incoming(i) == 0)
					Q.push_back(i);
			}
		}
	}

	// cycle / remaining edges?
	if (tm.count_edges() > 0)
		return std::make_tuple(vertex_list{}, false);

	return std::make_tuple(v, true);
}
}

#endif
