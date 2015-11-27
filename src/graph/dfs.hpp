#ifndef __GRAPH__DFS__HPP__
#define __GRAPH__DFS__HPP__

#include "adjmatrix.hpp"

namespace graph
{
/// \cond DEV
namespace detail
{
template <class Visitor>
static void recursive_dfs(
	const adjmatrix & adj, vertex id, Visitor & visitor, adjmatrix::visited_list & visited)
{
	// guard
	if (id >= adj.size())
		return;
	if (visited[id])
		return;

	// visit
	visited[id] = true;
	visitor(adj, id);

	// search deeper
	for (vertex i = 0; i < adj.size(); ++i)
		if ((i != id) && adj.get(id, i))
			recursive_dfs(adj, i, visitor, visited);
}
}
/// \endcond

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'depth first'.
///
/// \param[in] m The adjacency matrix to visit.
/// \param[in] v The starting vertex.
/// \param[in] visitor Visitor which gets called for each found vertex.
/// \return The visitor functor
///
template <class Visitor>
Visitor depth_first_search(const adjmatrix & m, vertex v, Visitor visitor)
{
	adjmatrix::visited_list visited(m.size(), false);
	detail::recursive_dfs(m, v, visitor, visited);
	return visitor;
}
}

#endif
