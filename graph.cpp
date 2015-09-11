#include <iostream>
#include "adj_matrix.hpp"
#include "graph_dfs.hpp"
#include "graph_toposort.hpp"
#include "graph_bfs.hpp"
#include "edge_property_map.hpp"

class Printer
{
public:
	void operator()(const graph::adj_matrix::vertex_t & v) const { std::cout << " " << v; }
};

int main(int, char **)
{
	using namespace graph;

	adj_matrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});

	std::cout << "Breadth First Search: ";
	breadth_first_search(m, 0, Printer{});
	std::cout << "\n";

	std::cout << "Depth First Search  : ";
	depth_first_search(m, 0, Printer{});
	std::cout << "\n";

	{
		adj_matrix::vertex_list v;
		std::cout << "Topological sorted  : ";
		if (topological_sort(m, v) == false) {
			std::cout << "FAILED: circle detected";
		} else {
			for_each(v.begin(), v.end(), Printer{});
		}
		std::cout << "\n";
	}

	{
		edge_property_map<float> ep(m);
		ep.prop(0, 1) = 0.5;
		ep.prop(0, 2) = 0.5;
		ep.prop(0, 3) = 0.5;
		ep.prop(1, 2) = 0.5;
		ep.prop(1, 3) = 0.5;
		ep.prop(2, 4) = 0.5;
		ep.prop(3, 4) = 0.5;
	}

	return 0;
}

