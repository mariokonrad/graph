#include <iostream>
#include <graph/dot.hpp>
#include <graph/adjmatrix.hpp>

int main(int, char **)
{
	auto vp = [](
		graph::vertex v) -> std::string { return (v % 2 == 0) ? "shape=rectangle" : ""; };
	auto ep = [](graph::edge) -> std::string { return "label=\"foo\""; };

	graph::adjmatrix m{5, {{0, 1}, {0, 2}, {1, 3}, {2, 3}, {1, 4}, {3, 4}}};
	std::cout << graph::dot(m, "bgcolor=green", "shape=circle,color=blue", "color=red", vp, ep);
	return 0;
}
