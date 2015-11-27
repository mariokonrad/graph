#ifndef __GRAPH__PATH__HPP__
#define __GRAPH__PATH__HPP__

#include <tuple>
#include <graph/adjmatrix.hpp>

namespace graph
{
std::tuple<adjmatrix::vertex_list, bool> shortest_path_dijkstra(
	const adjmatrix & m, vertex start, vertex destination);
}

#endif
