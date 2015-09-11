#ifndef __GRAPH__GRAPH_DFS__HPP__
#define __GRAPH__GRAPH_DFS__HPP__

#include "adj_matrix.hpp"

namespace graph
{

template <class Visitor>
static void r_depth_first_search(const adj_matrix & adj, adj_matrix::vertex_t id, Visitor & v,
	adj_matrix::visited_list & visited)
{
	// guard
	if (id >= adj.size())
		return;
	if (visited[id])
		return;

	// visit
	visited[id] = true;
	v(id);

	// search deeper
	for (adj_matrix::vertex_t i = 0; i < adj.size(); ++i)
		if ((i != id) && adj.edge(id, i))
			r_depth_first_search(adj, i, v, visited);
}

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'depth first'.
///
/// \param[in]  m       The adjacency matrix to visit.
/// \param[in]  v       The starting vertex.
/// \param[out] visitor Visitor which gets called for each found vertex.
template <class Visitor>
void depth_first_search(const adj_matrix & m, adj_matrix::vertex_t v, Visitor & visitor)
{
	adj_matrix::visited_list visited(m.size(), false);
	r_depth_first_search(m, v, visitor, visited);
}
}

#endif
