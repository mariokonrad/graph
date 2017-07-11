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

#ifndef GRAPH__MST__HPP
#define GRAPH__MST__HPP

#include <algorithm>
#include <limits>
#include <vector>
#include <graph/edge.hpp>
#include <graph/type_traits.hpp>
#include <utils/priority_queue.hpp>

namespace graph
{
/// \cond DEV
namespace detail
{
/// Detail implementation of the minimum spanning tree.
template <class Value, class Graph, class Accessor>
edge_list minimum_spanning_tree_prim(const Graph & g, vertex start, Accessor access)
{
	// prepare list of parents
	vertex_list parent(g.size(), vertex_invalid);

	// prepare container of costs
	std::vector<Value> cost(g.size(), std::numeric_limits<Value>::max());
	cost[start] = Value{};

	// prepare priority queue
	auto cmp = [&cost](vertex a, vertex b) -> bool { return cost[a] > cost[b]; };
	utils::priority_queue<vertex, decltype(cmp)> q(cmp, g.vertices());

	while (!q.empty()) {
		vertex u = q.top();
		q.pop();

		for (auto const & v : g.outgoing(u)) {
			if (std::find(std::begin(q), std::end(q), v) == std::end(q))
				continue;
			const Value alt = cost[u] + access({u, v});
			if (alt < cost[v]) {
				cost[v] = alt;
				parent[v] = u;
				q.update(); // priority criteria have been changed
			}
		}
	}

	// fill edge list with tree
	edge_list tree;
	tree.reserve(g.size());
	for (auto const & v : g.vertices())
		tree.push_back({parent[v], v});
	return tree;
}
}
/// \endcond

/// Computes the miminum spanning tree of the specified graph.
/// The values of the edges must represent their weight and
/// the graph must be bidirectional. The weight must be positive.
///
/// This implementation is far from optimized. In fact it is
/// a quite naive implementation. For demonstration purposes
/// sufficient.
///
/// \tparam Graph The graph type to visit.
///   Must provide the following features:
///   - type `value_type` which represents a single value within the graph (length of an edge)
///   - type `size_type` which represents a size type for the graph
///   - function `size_type size() const` which returns the number of nodes in the graph
///   - function `vertex_list vertices() const` which returns a `vertex_list` of all nodes
///   - function `vertex_list outgoing(vertex) const` which returns a `vertex_list` of
///     all nodes reachable from the specified one
///   - function `value_type at(edge) const` which returns the status of the specified edge.
///
/// \param[in] g The graph to generate the minimum spanning tree for.
/// \param[in] start Starting node.
/// \return A list of edges found for the minimum spanning tree.
///
/// complexity: O(n log n)
///
template <class Graph,
	typename = typename std::enable_if<detail::has_t_value_type<Graph>::value
			&& detail::has_t_size_type<Graph>::value && detail::has_f_size<Graph>::value
			&& detail::has_f_at<Graph>::value && detail::has_f_vertices<Graph>::value
			&& detail::has_f_outgoing<Graph>::value,
		void>::type>
edge_list minimum_spanning_tree_prim(const Graph & g, vertex start)
{
	using Value = typename Graph::value_type;
	return detail::minimum_spanning_tree_prim<Value>(
		g, start, [&g](edge e) { return g.at(e); });
}

/// Computes the miminum spanning tree of the specified graph.
/// The values of the edges must represent their weight and
/// the graph must be bidirectional. The weight must be positive.
///
/// This implementation is far from optimized. In fact it is
/// a quite naive implementation. For demonstration purposes
/// sufficient.
///
/// Has the same properties (complexity, implementation) as minimum_spanning_tree_prim()
///
/// \tparam Graph The graph type to visit.
///   Must provide the following features:
///   - function `size_type size() const` which returns the number of nodes in the graph
///   - function `vertex_list vertices() const` which returns a `vertex_list` of all nodes
///   - function `vertex_list outgoing(vertex) const` which returns a `vertex_list` of all nodes
///     reachable from the specified one
///
/// \tparam PropertyMap The mapping of edge to distance, must provide following features:
///   - type `mapped_type` which represents the distance type of an edge
///   - type `const_iterator`
///   - function `const_iterator find(edge) const` returning an iterator (pair of key, value)
///   - function `const_iterator end() const` returning an iterator to the end of the container
///
/// \param[in] g The graph to generate the minimum spanning tree for.
/// \param[in] start Starting node.
/// \param[in] p The property mapping, containing the distances of the nodes
/// \return A list of edges found for the minimum spanning tree.
///
template <class Graph, class PropertyMap,
	typename = typename std::enable_if<detail::has_t_size_type<Graph>::value
			&& detail::has_f_size<Graph>::value && detail::has_f_vertices<Graph>::value
			&& detail::has_f_outgoing<Graph>::value
			&& detail::has_t_mapped_type<PropertyMap>::value
			&& detail::has_t_const_iterator<PropertyMap>::value
			&& detail::has_f_find<PropertyMap>::value && detail::has_f_end<PropertyMap>::value,
		void>::type>
edge_list minimum_spanning_tree_prim(const Graph & g, const PropertyMap & p, vertex start)
{
	using Value = typename PropertyMap::mapped_type;
	return detail::minimum_spanning_tree_prim<Value>(g, start, [&p](edge e) -> Value {
		auto const i = p.find(e);
		if (i != p.end())
			return i->second;
		return {};
	});
}
}

#endif
