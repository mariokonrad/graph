#ifndef __GRAPH__GRAPH_PATH__HPP__
#define __GRAPH__GRAPH_PATH__HPP__

#include "adjmatrix.hpp"

namespace graph
{

/// Finds and returns the shortest path from the start to the destination
/// node within the specified graph.
///
/// The graph must have a shortest path. The edges within the graph
/// must specify their length.
///
/// This implementation is not optimized, also it is a rather naive implementation,
/// but sufficient for demonstration.
///
/// Complexity: O(n^2)
///
adjmatrix::vertex_list shortest_path_dijkstra(
	const adjmatrix & m, adjmatrix::vertex_t start, adjmatrix::vertex_t destination)
{
	using namespace std;

	// prepare list of predecessors
	const adjmatrix::vertex_t undefined = -1;
	adjmatrix::vertex_list predecessor(m.size());
	fill(begin(predecessor), end(predecessor), undefined);

	// prepare list of distances
	adjmatrix::vertex_value_list distance(m.size());
	fill(begin(distance), end(distance), numeric_limits<adjmatrix::vertex_value_t>::max());
	distance[start] = 0;

	// prepare list of nodes to process
	adjmatrix::vertex_list q;
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
		for (adjmatrix::vertex_list::size_type i = 0; i < q.size(); ++i) {
			adjmatrix::vertex_value_t dist_q = distance[q[i]];
			if ((dist_q >= 0) && (dist_q < dist_min)) {
				dist_min = dist_q;
				index_q = i;
				current = q[i];
			}
		}
		q.erase(begin(q) + index_q);

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
	adjmatrix::vertex_list path;
	while (current != undefined) {
		path.push_back(current);
		current = predecessor[current];
	}
	reverse(begin(path), end(path));

	return path;
}
}

#endif
