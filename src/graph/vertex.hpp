#ifndef __GRAPH__VERTEX__HPP__
#define __GRAPH__VERTEX__HPP__

#include <vector>
#include <limits>

namespace graph
{
/// Vertex identifier. Also used as index within adjacency matrices.
using vertex = std::size_t;

/// Indicates an invalid vertex.
enum : vertex { vertex_invalid = std::numeric_limits<vertex>::max() };

/// Container type for a list of vertices.
using vertex_list = std::vector<vertex>;

/// Internally used to keep track of visited vertices.
using visited_vertex_list = std::vector<bool>;
}

#endif
