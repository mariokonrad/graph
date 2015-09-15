#ifndef __GRAPH__PATH__HPP__
#define __GRAPH__PATH__HPP__

#include <graph/adjmatrix.hpp>

namespace graph
{
adjmatrix::vertex_list_t shortest_path_dijkstra(
	const adjmatrix & m, adjmatrix::vertex_t start, adjmatrix::vertex_t destination);
}

#endif
