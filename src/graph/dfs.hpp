#ifndef __GRAPH__DFS__HPP__
#define __GRAPH__DFS__HPP__

#include "adjmatrix.hpp"

namespace graph
{

namespace detail
{
template <class Visitor>
static void recursive_dfs(const adjmatrix & adj, adjmatrix::vertex_t id,
	Visitor & visitor, adjmatrix::visited_list_t & visited)
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
			recursive_dfs(adj, i, visitor, visited);
}
}

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'depth first'.
///
/// \param[in] m The adjacency matrix to visit.
/// \param[in] v The starting vertex.
/// \param[in] visitor Visitor which gets called for each found vertex.
/// \return The visitor functor
///
template <class Visitor>
Visitor depth_first_search(const adjmatrix & m, adjmatrix::vertex_t v, Visitor visitor)
{
	adjmatrix::visited_list_t visited(m.size(), false);
	detail::recursive_dfs(m, v, visitor, visited);
	return visitor;
}
}

#endif
