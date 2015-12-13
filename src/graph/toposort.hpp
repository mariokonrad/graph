#ifndef __GRAPH__TOPOSORT__HPP__
#define __GRAPH__TOPOSORT__HPP__

#include <tuple>
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
///   - `size()` which returns the number of nodes in the graph
///   - `at(edge)` which returns the status of the specified edge.
///   - `remove(edge)` which removes an edge from the graph
///   - `count_incoming(node)` which returns the number of incoming edges for a node
///   - `count_edges()` which returns the number of edges within the graph
///
/// \param[in] g The adjacency matrix.
/// \return A tuple containing the list and a status which is:
///   - \c true : sorting successful
///   - \c false : graph contains cycles
///
template <class Graph> std::tuple<vertex_list, bool> topological_sort(const Graph & g)
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
