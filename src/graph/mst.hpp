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

#ifndef __GRAPH__MST__HPP__
#define __GRAPH__MST__HPP__

#include <algorithm>
#include <limits>
#include <vector>
#include <graph/edge.hpp>

namespace graph
{
/// \cond DEV
namespace detail
{
/// Detail implementation of the minimum spanning tree.
template <class Value, class Graph, class Accessor>
edge_list minimum_spanning_tree_prim(const Graph & g, Accessor access)
{
	using namespace std;

	edge_list tree;
	tree.reserve(g.size());

	// cost (weight) of an edge to a certain node
	vector<Value> cost(g.size());
	fill(begin(cost), end(cost), numeric_limits<Value>::max());

	// node from which a certain node is reachable by cost[]
	vertex_list low_cost_edge(g.size());
	fill(begin(low_cost_edge), end(low_cost_edge), vertex_invalid);

	// setup queue of nodes to visit, initially all of them
	vertex_list q = g.vertices();

	// actual algorithm, start with the first node
	cost[0] = 0;
	while (!q.empty()) {

		// find node with minimal (valid) cost from still available nodes q
		vertex current = vertex_invalid;
		vertex index_q = vertex_invalid;
		Value cost_min = numeric_limits<Value>::max();
		for (vertex_list::size_type i = 0; i < q.size(); ++i) {
			Value cost_q = cost[q[i]];
			if ((cost_q >= 0) && (cost_q < cost_min)) {
				cost_min = cost_q;
				index_q = i;
				current = q[i];
			}
		}
		q.erase(begin(q) + index_q);

		// add node to tree
		tree.emplace_back(low_cost_edge[current], current);

		// from the current node, update all costs to adjacent nodes
		for (vertex node = 0; node < g.size(); ++node) {
			const Value w = access({current, node});
			if (w > 0) {
				if (find(begin(q), end(q), node) != end(q)) {
					if (w < cost[node]) {
						cost[node] = w;
						low_cost_edge[node] = current;
					}
				}
			}
		}
	}

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
///   - function `size()` which returns the number of nodes in the graph
///   - function `at(edge)` which returns the status of the specified edge.
///   - function `vertices()` which returns a `vertex_list` of all nodes
///
/// \param[in] g The graph to generate the minimum spanning tree for.
/// \return A list of edges found for the minimum spanning tree.
///
/// \todo Implement algorithm using priority queue
///
/// complexity: O(n^2)
///
template <class Graph> edge_list minimum_spanning_tree_prim(const Graph & g)
{
	return detail::minimum_spanning_tree_prim<typename Graph::value_type>(
		g, [&g](edge e) { return g.at(e); });
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
///   - function `size()` which returns the number of nodes in the graph
///   - function `at(edge)` which returns the status of the specified edge.
///   - function `vertices()` which returns a `vertex_list` of all nodes
///
/// \tparam PropertyMap The mapping of edge to distance, must provide following features:
///   - type `mapped_type` which represents the distance type of an edge
///   - function `find(edge)` returning an iterator (pair of key, value)
///   - function `end()` returning an iterator to the end of the container
///
/// \param[in] g The graph to generate the minimum spanning tree for.
/// \param[in] p The property mapping, containing the distances of the nodes
/// \return A list of edges found for the minimum spanning tree.
///
template <class Graph, class PropertyMap>
edge_list minimum_spanning_tree_prim(const Graph & g, const PropertyMap & p)
{
	using Value = typename PropertyMap::mapped_type;
	return detail::minimum_spanning_tree_prim<Value>(g, [&p](edge e) -> Value {
		auto const i = p.find(e);
		if (i != p.end())
			return i->second;
		return {};
	});
}
}

#endif
