#ifndef __GRAPH__GRAPH_DFS__HPP__
#define __GRAPH__GRAPH_DFS__HPP__

#include "adjmatrix.hpp"

namespace graph
{

namespace detail
{
template <class Visitor>
static void recursive_dfs(const adjmatrix & adj, adjmatrix::vertex_t id,
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
	adjmatrix::visited_list visited(m.size(), false);
	detail::recursive_dfs(m, v, visitor, visited);
	return visitor;
}
}

#endif
