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

	adj_matrix m(5);

	m.add(0, 1);
	m.add(0, 2);
	m.add(0, 3);
	m.add(1, 2);
	m.add(1, 3);
	m.add(2, 4);
	m.add(3, 4);

	{
		std::cout << "Breadth First Search: ";
		Printer p;
		breadth_first_search(m, 0, p);
		std::cout << "\n";
	}

	{
		std::cout << "Depth First Search  : ";
		Printer p;
		depth_first_search(m, 0, p);
		std::cout << "\n";
	}

	{
		adj_matrix::vertex_list v;
		std::cout << "Topological sorted  : ";
		if (topological_sort(m, v) == false) {
			std::cout << "FAILED: circle detected";
		} else {
			Printer p;
			for_each(v.begin(), v.end(), p);
		}
		std::cout << "\n";
	}

	{
		using EP = edge_property_map<float>;
		EP ep(m.size());
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

