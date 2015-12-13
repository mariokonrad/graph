#ifndef __GRAPH__DFS__HPP__
#define __GRAPH__DFS__HPP__

#include "adjmatrix.hpp"

namespace graph
{
/// \cond DEV
namespace detail
{
template <class Graph, class Visitor>
static void recursive_dfs(
	const Graph & g, vertex id, Visitor & visitor, adjmatrix::visited_list & visited)
{
	// guard
	if (id >= g.size())
		return;
	if (visited[id])
		return;

	// visit
	visited[id] = true;
	visitor(g, id);

	// search deeper
	for (vertex i = 0; i < g.size(); ++i)
		if ((i != id) && g.at({id, i}))
			recursive_dfs(g, i, visitor, visited);
}
}
/// \endcond

/// This algorithm searches the graph and calls the visitor for each
/// vertex. The strategy is 'depth first'.
///
/// \tparam Graph The graph type.
/// \tparam Visitor The visitor type for the search.
/// \param[in] g The graph to visit.
/// \param[in] v The starting vertex.
/// \param[in] visitor Visitor which gets called for each found vertex.
/// \return The visitor functor
///
template <class Graph, class Visitor>
Visitor depth_first_search(const Graph & g, vertex v, Visitor visitor)
{
	adjmatrix::visited_list visited(g.size(), false);
	detail::recursive_dfs(g, v, visitor, visited);
	return visitor;
}
}

#endif
