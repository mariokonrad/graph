#ifndef __GRAPH__PATH__HPP__
#define __GRAPH__PATH__HPP__

#include <algorithm>
#include <tuple>
#include <graph/edge.hpp>

namespace graph
{
/// Finds and returns the shortest path from the start to the destination
/// node within the specified graph. If the destination is not reachable,
/// the second return value will indicate this with being \c false.
///
/// This implementation is not optimized, also it is a rather naive implementation,
/// but sufficient for demonstration.
///
/// \todo Implement algorithm using priority queue
///
/// Complexity: O(n^2)
///
/// \tparam Graph The graph type to visit.
///   Must provide the following features:
///   - a type `value_type` which represents a single value within the graph (length of an edge)
///   - a type `value_list` which is a container of edge lengths
///   - `size()` which returns the number of nodes in the graph
///   - `at(edge)` which returns the status of the specified edge.
///   - `vertices()` which returns a `vertex_list` of all nodes
///   - `neighbors_of(node)` which returns a `vertex_list` of all neighbors of the specified node
///
/// \param[in] g The graph
/// \param[in] start The staring node
/// \param[in] destination The destination node
/// \return A tuple with the following information:
///   - list of vertices from start to destination (inclusive)
///   - status about success, if false: destination not reachable
///
template <class Graph>
std::tuple<vertex_list, bool> shortest_path_dijkstra(
	const Graph & g, vertex start, vertex destination)
{
	using namespace std;

	using value_type = typename Graph::value_type;
	using value_list = typename Graph::value_list;

	// prepare list of predecessors
	constexpr vertex undefined = vertex_invalid;
	vertex_list predecessor(g.size());
	fill(begin(predecessor), end(predecessor), undefined);

	// prepare list of distances
	value_list distance(g.size());
	fill(begin(distance), end(distance), numeric_limits<value_type>::max());
	distance[start] = 0;

	// prepare list of nodes to process
	vertex_list q;
	q.reserve(g.size());
	for (auto const & vertex : g.vertices())
		q.push_back(vertex);

	// the actual algorithm
	vertex current = undefined;
	while (!q.empty()) {

		// find node with minimal distance from nodes q
		current = undefined;
		vertex index_q = undefined;
		value_type dist_min = numeric_limits<value_type>::max();
		for (vertex_list::size_type i = 0; i < q.size(); ++i) {
			value_type dist_q = distance[q[i]];
			if ((dist_q >= 0) && (dist_q < dist_min)) {
				dist_min = dist_q;
				index_q = i;
				current = q[i];
			}
		}
		if (index_q == undefined)
			return std::make_tuple(vertex_list{}, false);
		q.erase(begin(q) + index_q);

		// destination reached?
		if (current == destination)
			break;

		// check all remaining neighbors of current node and update distances
		for (auto const & node : g.neighbors_of(current)) {
			if (find(begin(q), end(q), node) != end(q)) {
				const value_type d = distance[current] + g.at({current, node});
				if (d < distance[node]) {
					distance[node] = d;
					predecessor[node] = current;
				}
			}
		}
	}

	// process predecessors into path
	vertex_list path;
	while (current != undefined) {
		path.push_back(current);
		current = predecessor[current];
	}
	reverse(begin(path), end(path));

	return std::make_tuple(path, true);
}
}

#endif
