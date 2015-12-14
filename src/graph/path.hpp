#ifndef __GRAPH__PATH__HPP__
#define __GRAPH__PATH__HPP__

#include <algorithm>
#include <tuple>
#include <vector>
#include <graph/edge.hpp>

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
	using namespace std;

	// prepare list of predecessors
	constexpr vertex undefined = vertex_invalid;
	vertex_list predecessor(g.size());
	fill(begin(predecessor), end(predecessor), undefined);

	// prepare list of distances
	vector<Value> distance(g.size());
	fill(begin(distance), end(distance), numeric_limits<Value>::max());
	distance[start] = Value{};

	// prepare list of nodes to process
	vertex_list q = g.vertices();

	// the actual algorithm
	vertex current = undefined;
	while (!q.empty()) {

		// find node with minimal distance from nodes q
		current = undefined;
		vertex index_q = undefined;
		Value dist_min = numeric_limits<Value>::max();
		for (vertex_list::size_type i = 0; i < q.size(); ++i) {
			Value dist_q = distance[q[i]];
			if ((dist_q >= 0) && (dist_q < dist_min)) {
				dist_min = dist_q;
				index_q = i;
				current = q[i];
			}
		}
		if (index_q == undefined)
			return make_tuple(vertex_list{}, false);
		q.erase(begin(q) + index_q);

		// destination reached?
		if (current == destination)
			break;

		// check all remaining neighbors of current node and update distances
		for (auto const & node : g.outgoing(current)) {
			if (find(begin(q), end(q), node) != end(q)) {
				const Value d = distance[current] + access({current, node});
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

	return make_tuple(path, true);
}
}
/// \endcond

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
///   - type `value_type` which represents a single value within the graph (length of an edge)
///   - function `size()` which returns the number of nodes in the graph
///   - function `at(edge)` which returns the status of the specified edge.
///   - function `vertices()` which returns a `vertex_list` of all nodes
///   - function `outgoing(node)` which returns a `vertex_list` of all neighbors of the
///     specified node
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
	return detail::shortest_path_dijkstra<typename Graph::value_type>(
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
///   - function `size()` which returns the number of nodes in the graph
///   - function `vertices()` which returns a `vertex_list` of all nodes
///   - function `outgoing(node)` which returns a `vertex_list` of all neighbors of the
///     specified node
///
/// \tparam PropertyMap The mapping of edge to distance, must provide following features:
///   - type `mapped_type` which represents the distance type of an edge
///   - function `at(edge)` to access the distance information for each edge
///
/// \param[in] g The graph
/// \param[in] p The property mapping, containing the distances of the nodes
/// \param[in] start The staring node
/// \param[in] destination The destination node
/// \return A tuple with the following information:
///   - list of vertices from start to destination (inclusive)
///   - status about success, if false: destination not reachable
///
template <class Graph, class PropertyMap>
std::tuple<vertex_list, bool> shortest_path_dijkstra(
	const Graph & g, const PropertyMap & p, vertex start, vertex destination)
{
	return detail::shortest_path_dijkstra<typename PropertyMap::mapped_type>(
		g, [&p](edge e) { return p.at(e); }, start, destination);
}
}

#endif
