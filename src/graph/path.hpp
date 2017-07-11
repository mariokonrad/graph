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

#ifndef GRAPH__PATH__HPP
#define GRAPH__PATH__HPP

#include <algorithm>
#include <tuple>
#include <vector>
#include <graph/type_traits.hpp>
#include <graph/edge.hpp>
#include <utils/priority_queue.hpp>

namespace graph
{
/// \cond DEV
namespace detail
{
/// Detail implementation of the shortest path finding algorithm.
template <class Value, class Graph, class Accessor>
std::tuple<vertex_list, bool> shortest_path_dijkstra(
	const Graph & g, Accessor access, vertex start, vertex destination)
{
	// prepare list of predecessors
	constexpr vertex undefined = vertex_invalid;
	vertex_list predecessor(g.size(), undefined);

	// prepare list of distances
	std::vector<Value> distance(g.size(), std::numeric_limits<Value>::max());
	distance[start] = Value{};

	// prepare priority queue
	auto cmp = [&distance](vertex a, vertex b) -> bool { return distance[a] > distance[b]; };
	utils::priority_queue<vertex, decltype(cmp)> q(cmp, g.vertices());

	vertex u = undefined;
	while (!q.empty()) {
		u = q.top();
		q.pop();

		if (u == destination)
			break;

		for (auto const & v : g.outgoing(u)) {
			const Value alt = distance[u] + access({u, v});
			if (alt < distance[v]) {
				distance[v] = alt;
				predecessor[v] = u;
				q.update(); // priority criteria have been changed
			}
		}
	}

	// create path
	vertex_list path;
	while ((u != start) && (u != undefined)) {
		path.push_back(u);
		u = predecessor[u];
	}

	// path may not exist
	if (u == undefined)
		return std::make_tuple(vertex_list{}, false);

	path.push_back(u);
	std::reverse(std::begin(path), std::end(path));
	return std::make_tuple(path, true);
}
}
/// \endcond

/// Finds and returns the shortest path from the start to the destination
/// node within the specified graph. If the destination is not reachable,
/// the second return value will indicate this with being \c false.
///
/// This implementation is not optimized, also it is a rather naive implementation,
/// but sufficient for demonstration. At least it uses a priority queue.
///
/// Complexity: O(n log n)
///
/// \tparam Graph The graph type to visit.
///   Must provide the following features:
///   - type `value_type` which represents a single value within the graph (length of an edge)
///   - type `size_type` which represents a size type for the graph
///   - function `size_type size() const` which returns the number of nodes in the graph
///   - function `vertex_list vertices() const` which returns a `vertex_list` of all nodes
///   - function `vertex_list outgoing(vertex) const` which returns a `vertex_list` of all
///     neighbors of the specified node
///   - function `value_type at(edge) const` which returns the status of the specified edge.
///
/// \param[in] g The graph
/// \param[in] start The staring node
/// \param[in] destination The destination node
/// \return A tuple with the following information:
///   - list of vertices from start to destination (inclusive)
///   - status about success, if false: destination not reachable
///
template <class Graph,
	typename = typename std::enable_if<detail::has_t_value_type<Graph>::value
			&& detail::has_t_size_type<Graph>::value && detail::has_f_size<Graph>::value
			&& detail::has_f_at<Graph>::value && detail::has_f_vertices<Graph>::value
			&& detail::has_f_outgoing<Graph>::value,
		void>::type>
std::tuple<vertex_list, bool> shortest_path_dijkstra(
	const Graph & g, vertex start, vertex destination)
{
	using Value = typename Graph::value_type;
	return detail::shortest_path_dijkstra<Value>(
		g, [&g](edge e) { return g.at(e); }, start, destination);
}

/// This function does basically the same as shortest_path_dijkstra() with the
/// difference of having the distances of the edges provided by a property map
/// instead of encoded directly into the graph.
///
/// Has the same properties (complexity, implementation) as shortest_path_dijkstra()
///
/// \tparam Graph The graph type to visit.
///   Must provide the following features:
///   - function `size_type size() const` which returns the number of nodes in the graph
///   - function `vertex_list vertices() const` which returns a `vertex_list` of all nodes
///   - function `vertex_list outgoing(vertex) const` which returns a `vertex_list` of all
///     neighbors of the specified node
///
/// \tparam PropertyMap The mapping of edge to distance, must provide following features:
///   - type `mapped_type` which represents the distance type of an edge
///   - type `const_iterator`
///   - function `const_iterator find(edge) const` returning an iterator (pair of key, value)
///   - function `const_iterator end() const` returning an iterator to the end of the container
///
/// \param[in] g The graph
/// \param[in] p The property mapping, containing the distances of the nodes
/// \param[in] start The staring node
/// \param[in] destination The destination node
/// \return A tuple with the following information:
///   - list of vertices from start to destination (inclusive)
///   - status about success, if false: destination not reachable
///
template <class Graph, class PropertyMap,
	typename = typename std::enable_if<detail::has_t_size_type<Graph>::value
			&& detail::has_f_size<Graph>::value && detail::has_f_vertices<Graph>::value
			&& detail::has_f_outgoing<Graph>::value
			&& detail::has_t_mapped_type<PropertyMap>::value
			&& detail::has_t_const_iterator<PropertyMap>::value
			&& detail::has_f_find<PropertyMap>::value && detail::has_f_end<PropertyMap>::value,
		void>::type>
std::tuple<vertex_list, bool> shortest_path_dijkstra(
	const Graph & g, const PropertyMap & p, vertex start, vertex destination)
{
	using Value = typename PropertyMap::mapped_type;
	return detail::shortest_path_dijkstra<Value>(g, [&p](edge e) -> Value {
		auto const i = p.find(e);
		if (i != p.end())
			return i->second;
		return {};
	}, start, destination);
}
}

#endif
