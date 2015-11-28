#ifndef __GRAPH__MST__HPP__
#define __GRAPH__MST__HPP__

#include <graph/adjmatrix.hpp>

namespace graph
{
edge_list minimum_spanning_tree_prim(const adjmatrix & m);
}

#endif
