#ifndef __GRAPH__DOT_PRINT__HPP__
#define __GRAPH__DOT_PRINT__HPP__

#include <string>
#include <sstream>
#include <graph/adjmatrix.hpp>

namespace graph
{
/// Renders the specified graph to a string in the Dot (graphviz)
/// format.
///
/// \param[in] m The graph to render
/// \return The string, representing the graph in the Dot language
std::string dot(const adjmatrix & m)
{
	std::ostringstream s;

	s << "digraph G {\n";
	s << "\t"
	  << "node [shape=circle];\n";
	for (auto const & e : m.edges()) {
		s << "\t" << e.from << " -> " << e.to << ";\n";
	}
	s << "}\n";

	return s.str();
}
}

#endif
