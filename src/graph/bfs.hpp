#ifndef __GRAPH__BFS__HPP__
#define __GRAPH__BFS__HPP__

#include <queue>
#include "adjmatrix.hpp"

namespace graph
{
/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'breadth first'.
///
/// \tparam Graph The graph type to visit.
/// \tparam Visitor The visitor type.
/// \param[in] g The adjacency matrix to visit.
/// \param[in] v The starting vertex.
/// \param[in] visitor Visitor which gets called for each found vertex.
/// \return The visitor functor
///
template <class Graph, class Visitor>
Visitor breadth_first_search(const Graph & g, vertex v, Visitor visitor)
{
	if (v >= g.size())
		return visitor;

	std::queue<vertex> q;
	adjmatrix::visited_list gray(g.size(), false);
	adjmatrix::visited_list black(g.size(), false);

	// starting vertex is gray and put into queue
	gray[v] = true;
	q.push(v);

	while (q.size() > 0) {
		// remove first in queue
		vertex u = q.front();
		q.pop();

		// all white successors of u
		for (vertex i = 0; i < g.size(); ++i) {
			if (!gray[i] && !black[i] && g.get(u, i)) {
				gray[i] = true;
				q.push(i);
			}
		}

		// visit and mark vertex
		black[u] = true;
		visitor(g, u);
	}
	return visitor;
}
}

#endif
