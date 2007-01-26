#ifndef __GRAPH__GRAPH_BFS__HPP__
#define __GRAPH__GRAPH_BFS__HPP__

#include "adj_matrix.hpp"
#include <queue>

namespace graph {

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'breadth first'.
///
/// \param[in]  m       The adjacency matrix to visit.
/// \param[in]  v       The starting vertex.
/// \param[out] visitor Visitor which gets called for each found vertex.
template <class Visitor, typename ADJ_MATRIX>
void breadth_first_search(const ADJ_MATRIX & m,
	typename ADJ_MATRIX::vertex_t v, Visitor & visitor)
{
	std::queue<typename ADJ_MATRIX::vertex_t> q;
	typename ADJ_MATRIX::visited_list gray(m.size(), false);
	typename ADJ_MATRIX::visited_list black(m.size(), false);

	// starting vertex is gray and put into queue
	gray[v] = true;
	q.push(v);

	while (q.size() > 0) {
		// remove first in queue
		typename ADJ_MATRIX::vertex_t u = q.front(); q.pop();

		// all white successors of u
		for (typename ADJ_MATRIX::vertex_t i = 0; i < m.size(); ++i) {
			if (!gray[i] && !black[i] && m.edge(u, i)) {
				gray[i] = true;
				q.push(i);
			}
		}

		// visit and mark vertex
		black[u] = true;
		visitor(u);
	}
}

}

#endif
