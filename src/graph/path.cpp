#include "path.hpp"
#include <algorithm>

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
/// \param[in] m The graph
/// \param[in] start The staring node
/// \param[in] destination The destination node
/// \return A tuple with the following information:
///   - list of vertices from start to destination (inclusive)
///   - status about success, if false: destination not reachable
///
std::tuple<adjmatrix::vertex_list_t, bool> shortest_path_dijkstra(
	const adjmatrix & m, adjmatrix::vertex_t start, adjmatrix::vertex_t destination)
{
	using namespace std;

	// prepare list of predecessors
	constexpr adjmatrix::vertex_t undefined = -1;
	adjmatrix::vertex_list_t predecessor(m.size());
	fill(begin(predecessor), end(predecessor), undefined);

	// prepare list of distances
	adjmatrix::vertex_value_list_t distance(m.size());
	fill(begin(distance), end(distance), numeric_limits<adjmatrix::vertex_value_t>::max());
	distance[start] = 0;

	// prepare list of nodes to process
	adjmatrix::vertex_list_t q;
	q.reserve(m.size());
	for (auto const & vertex : m.vertices())
		q.push_back(vertex);

	// the actual algorithm
	adjmatrix::vertex_t current = undefined;
	while (!q.empty()) {

		// find node with minimal distance from nodes q
		current = undefined;
		adjmatrix::vertex_t index_q = undefined;
		adjmatrix::vertex_value_t dist_min = numeric_limits<adjmatrix::vertex_value_t>::max();
		for (adjmatrix::vertex_list_t::size_type i = 0; i < q.size(); ++i) {
			adjmatrix::vertex_value_t dist_q = distance[q[i]];
			if ((dist_q >= 0) && (dist_q < dist_min)) {
				dist_min = dist_q;
				index_q = i;
				current = q[i];
			}
		}
		if (index_q == undefined)
			return std::make_tuple(adjmatrix::vertex_list_t{}, false);
		q.erase(begin(q) + index_q);

		// destination reached?
		if (current == destination)
			break;

		// check all remaining neighbors of current node and update distances
		for (auto const & node : m.neighbors_of(current)) {
			if (find(begin(q), end(q), node) != end(q)) {
				const adjmatrix::vertex_value_t d = distance[current] + m.edge(current, node);
				if (d < distance[node]) {
					distance[node] = d;
					predecessor[node] = current;
				}
			}
		}
	}

	// process predecessors into path
	adjmatrix::vertex_list_t path;
	while (current != undefined) {
		path.push_back(current);
		current = predecessor[current];
	}
	reverse(begin(path), end(path));

	return std::make_tuple(path, true);
}
}
