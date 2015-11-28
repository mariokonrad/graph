#ifndef __GRAPH__TOPOSORT__HPP__
#define __GRAPH__TOPOSORT__HPP__

#include <tuple>
#include <graph/adjmatrix.hpp>

namespace graph
{
std::tuple<vertex_list, bool> topological_sort(const adjmatrix & g);
}

#endif
