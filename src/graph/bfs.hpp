#ifndef __GRAPH__BFS__HPP__
#define __GRAPH__BFS__HPP__

#include <queue>
#include "adjmatrix.hpp"

namespace graph
{
/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'breadth first'.
///
/// \param[in] m The adjacency matrix to visit.
/// \param[in] v The starting vertex.
/// \param[in] visitor Visitor which gets called for each found vertex.
/// \return The visitor functor
///
template <class Visitor>
Visitor breadth_first_search(const adjmatrix & m, vertex v, Visitor visitor)
{
	if (v >= m.size())
		return visitor;

	std::queue<vertex> q;
	adjmatrix::visited_list gray(m.size(), false);
	adjmatrix::visited_list black(m.size(), false);

	// starting vertex is gray and put into queue
	gray[v] = true;
	q.push(v);

	while (q.size() > 0) {
		// remove first in queue
		vertex u = q.front();
		q.pop();

		// all white successors of u
		for (vertex i = 0; i < m.size(); ++i) {
			if (!gray[i] && !black[i] && m.get(u, i)) {
				gray[i] = true;
				q.push(i);
			}
		}

		// visit and mark vertex
		black[u] = true;
		visitor(m, u);
	}
	return visitor;
}
}

#endif
