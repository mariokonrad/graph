#ifndef __GRAPH__GRAPH_TOPOSORT__HPP__
#define __GRAPH__GRAPH_TOPOSORT__HPP__

#include "adj_matrix.hpp"

namespace graph {

/// This algorithm adds the vertices of the specified matrix
/// to the vertex list in topological order. The graph must
/// be free of cycles to determine a topological order.
///
/// \param[in]  m The adjacency matrix.
/// \param[out] v The resulting vertex list.
/// \return true=sorting successful, false=graph contains cycles.
template <typename ADJ_MATRIX>
bool topological_sort(const ADJ_MATRIX & m,
	typename ADJ_MATRIX::vertex_list & v)
{
	// copy of matrix to work on (remove edges)
	ADJ_MATRIX tm(m);

	// all nodes with no incoming edges
	typename ADJ_MATRIX::vertex_list Q;
	for (typename ADJ_MATRIX::vertex_t i = 0; i < m.size(); ++i)
		if (tm.num_incoming(i) == 0)
			Q.push_back(i);

	// sort
	while (Q.size() > 0) {
		// remove node from Q
		typename ADJ_MATRIX::vertex_t node = Q.front();
		Q.erase(Q.begin());

		// node is member of the result vector
		v.push_back(node);

		for (typename ADJ_MATRIX::vertex_t i = 0; i < tm.size(); ++i) {
			if (i == node) continue; // not to self
			if (tm.edge(node, i)) {
				tm.remove(node, i); // remove edge from graph

				// has i other incoming edges?
				if (tm.num_incoming(i) == 0) Q.push_back(i);
			}
		}
	}

	// remaining edges?
	if (tm.num_edges() > 0) return false; // cycle!

	return true;
}

}

#endif
