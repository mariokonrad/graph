#ifndef __GRAPH__DOT_PRINT__HPP__
#define __GRAPH__DOT_PRINT__HPP__

#include <string>

namespace graph
{
class adjmatrix; // forward declaration

std::string dot(const adjmatrix & m);
}

#endif
