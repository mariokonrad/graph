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
std::tuple<adjmatrix::vertex_list, bool> shortest_path_dijkstra(
	const adjmatrix & m, vertex start, vertex destination)
{
	using namespace std;

	// prepare list of predecessors
	constexpr vertex undefined = -1;
	adjmatrix::vertex_list predecessor(m.size());
	fill(begin(predecessor), end(predecessor), undefined);

	// prepare list of distances
	adjmatrix::value_list distance(m.size());
	fill(begin(distance), end(distance), numeric_limits<adjmatrix::value_type>::max());
	distance[start] = 0;

	// prepare list of nodes to process
	adjmatrix::vertex_list q;
	q.reserve(m.size());
	for (auto const & vertex : m.vertices())
		q.push_back(vertex);

	// the actual algorithm
	vertex current = undefined;
	while (!q.empty()) {

		// find node with minimal distance from nodes q
		current = undefined;
		vertex index_q = undefined;
		adjmatrix::value_type dist_min = numeric_limits<adjmatrix::value_type>::max();
		for (adjmatrix::vertex_list::size_type i = 0; i < q.size(); ++i) {
			adjmatrix::value_type dist_q = distance[q[i]];
			if ((dist_q >= 0) && (dist_q < dist_min)) {
				dist_min = dist_q;
				index_q = i;
				current = q[i];
			}
		}
		if (index_q == undefined)
			return std::make_tuple(adjmatrix::vertex_list{}, false);
		q.erase(begin(q) + index_q);

		// destination reached?
		if (current == destination)
			break;

		// check all remaining neighbors of current node and update distances
		for (auto const & node : m.neighbors_of(current)) {
			if (find(begin(q), end(q), node) != end(q)) {
				const adjmatrix::value_type d = distance[current] + m.get(current, node);
				if (d < distance[node]) {
					distance[node] = d;
					predecessor[node] = current;
				}
			}
		}
	}

	// process predecessors into path
	adjmatrix::vertex_list path;
	while (current != undefined) {
		path.push_back(current);
		current = predecessor[current];
	}
	reverse(begin(path), end(path));

	return std::make_tuple(path, true);
}
}
