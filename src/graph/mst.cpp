#include "mst.hpp"
#include <limits>
#include <algorithm>

namespace graph
{
/// Computes the miminum spanning tree of the specified graph.
/// The values of the edges must represent their weight and
/// the graph must be bidirectional. The weight must be positive.
///
/// This implementation is far from optimized. In fact it is
/// a quite naive implementation. For demonstration purposes
/// sufficient.
///
/// \param[in] g The graph to generate the minimum spanning tree for.
/// \return A list of edges found for the minimum spanning tree.
///
/// \todo Implement algorithm using priority queue
///
/// complexity: O(n^2)
///
adjmatrix::edge_list minimum_spanning_tree_prim(const adjmatrix & g)
{
	static const vertex invalid = -1;

	adjmatrix::edge_list tree;
	tree.reserve(g.size());

	// cost (weight) of an edge to a certain node
	std::vector<adjmatrix::value_type> cost(g.size());
	fill(begin(cost), end(cost), std::numeric_limits<adjmatrix::value_type>::max());

	// node from which a certain node is reachable by cost[]
	adjmatrix::vertex_list low_cost_edge(g.size());
	fill(begin(low_cost_edge), end(low_cost_edge), invalid);

	// setup queue of nodes to visit, initially all of them
	adjmatrix::vertex_list q(g.size());
	std::iota(begin(q), end(q), 0);

	// actual algorithm, start with the first node
	cost[0] = 0;
	while (!q.empty()) {

		// find node with minimal (valid) cost from still available nodes q
		vertex current = invalid;
		vertex index_q = invalid;
		adjmatrix::value_type cost_min = std::numeric_limits<adjmatrix::value_type>::max();
		for (adjmatrix::vertex_list::size_type i = 0; i < q.size(); ++i) {
			adjmatrix::value_type cost_q = cost[q[i]];
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
			const adjmatrix::value_type w = g.get(current, node);
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
