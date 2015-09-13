#ifndef __GRAPH__GRAPH_DFS__HPP__
#define __GRAPH__GRAPH_DFS__HPP__

#include "adjmatrix.hpp"

namespace graph
{

template <class Visitor>
static void r_depth_first_search(const adjmatrix & adj, adjmatrix::vertex_t id,
	Visitor & visitor, adjmatrix::visited_list & visited)
{
	// guard
	if (id >= adj.size())
		return;
	if (visited[id])
		return;

	// visit
	visited[id] = true;
	visitor(id);

	// search deeper
	for (adjmatrix::vertex_t i = 0; i < adj.size(); ++i)
		if ((i != id) && adj.edge(id, i))
			r_depth_first_search(adj, i, visitor, visited);
}

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'depth first'.
///
/// \param[in] m The adjacency matrix to visit.
/// \param[in] v The starting vertex.
/// \param[out] visitor Visitor which gets called for each found vertex.
template <class Visitor>
Visitor depth_first_search(const adjmatrix & m, adjmatrix::vertex_t v, Visitor visitor)
{
	adjmatrix::visited_list visited(m.size(), false);
	r_depth_first_search(m, v, visitor, visited);
	return visitor;
}
}

#endif
