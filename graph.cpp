#include <iostream>
#include "adj_matrix.hpp"
#include "graph_dfs.hpp"
#include "graph_toposort.hpp"
#include "graph_bfs.hpp"
#include "graph_mst.hpp"
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
		ep.prop(0, 1) = 0.1;
		ep.prop(0, 2) = 0.2;
		ep.prop(0, 3) = 0.3;
		ep.prop(1, 2) = 0.4;
		ep.prop(1, 3) = 0.5;
		ep.prop(2, 4) = 0.6;
		ep.prop(3, 4) = 0.7;

		std::cout << "Edge Properties:\n";
		for (auto const & edge : m.edges()) {
			std::cout << "  " << edge.from << " -> " << edge.to << " : " << ep[edge] << "\n";
		}
	}

	{
		adj_matrix m1{4};
		m1.add(0, 1, true, 2);
		m1.add(0, 3, true, 1);
		m1.add(1, 3, true, 2);
		m1.add(2, 3, true, 3);

		std::cout << "Minimum Spanning Tree (Prim):\n";
		for (auto const & edge : graph::minimum_spanning_tree_prim(m1)) {
			std::cout << "  " << edge.from << " -> " << edge.to << "\n";
		}
	}

	{
		adj_matrix m1{6};
		m1.add(0, 1, true, 1);
		m1.add(0, 3, true, 4);
		m1.add(0, 4, true, 3);
		m1.add(1, 3, true, 4);
		m1.add(1, 4, true, 2);
		m1.add(2, 4, true, 4);
		m1.add(2, 5, true, 5);
		m1.add(3, 4, true, 4);
		m1.add(4, 5, true, 7);

		std::cout << "Minimum Spanning Tree (Prim):\n";
		for (auto const & edge : graph::minimum_spanning_tree_prim(m1)) {
			std::cout << "  " << edge.from << " -> " << edge.to << "\n";
		}
	}

	return 0;
}

