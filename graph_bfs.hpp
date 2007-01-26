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
template <class Visitor>
void breadth_first_search(const adj_matrix & m,
	adj_matrix::vertex_t v, Visitor & visitor)
{
	std::queue<adj_matrix::vertex_t> q;
	adj_matrix::visited_list gray(m.size(), false);
	adj_matrix::visited_list black(m.size(), false);

	// starting vertex is gray and put into queue
	gray[v] = true;
	q.push(v);

	while (q.size() > 0) {
		// remove first in queue
		adj_matrix::vertex_t u = q.front(); q.pop();

		// all white successors of u
		for (adj_matrix::vertex_t i = 0; i < m.size(); ++i) {
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
