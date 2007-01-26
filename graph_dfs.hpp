#ifndef __GRAPH__GRAPH_DFS__HPP__
#define __GRAPH__GRAPH_DFS__HPP__

#include "adj_matrix.hpp"

namespace graph {

template <class Visitor, typename ADJ_MATRIX>
static void r_depth_first_search(const ADJ_MATRIX & adj,
	typename ADJ_MATRIX::vertex_t id,
	Visitor & v, typename ADJ_MATRIX::visited_list & visited)
{
	// guard
	if (id >= adj.size()) return;
	if (visited[id]) return;

	// visit
	visited[id] = true;
	v(id);

	// search deeper
	for (typename ADJ_MATRIX::vertex_t i = 0; i < adj.size(); ++i)
		if ((i != id) && adj.edge(id, i))
			r_depth_first_search(adj, i, v, visited);
}

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'depth first'.
///
/// \param[in]  m       The adjacency matrix to visit.
/// \param[in]  v       The starting vertex.
/// \param[out] visitor Visitor which gets called for each found vertex.
template <class Visitor, typename ADJ_MATRIX>
void depth_first_search(const ADJ_MATRIX & m,
	typename ADJ_MATRIX::vertex_t v, Visitor & visitor)
{
	typename ADJ_MATRIX::visited_list visited(m.size(), false);
	r_depth_first_search(m, v, visitor, visited);
}

}

#endif
