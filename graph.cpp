#include <iostream>
#include "adj_matrix.hpp"
#include "graph_dfs.hpp"
#include "graph_toposort.hpp"
#include "graph_bfs.hpp"
#include "graph_mst.hpp"
#include "graph_path.hpp"
#include "property_map.hpp"

class Printer
{
public:
	void operator()(const graph::adj_matrix::vertex_t & v) const { std::cout << " " << v; }
};

void test_bfs()
{
	using namespace graph;
	adj_matrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
	std::cout << "Breadth First Search: ";
	breadth_first_search(m, 0, Printer{});
	std::cout << "\n";
}

void test_dfs()
{
	using namespace graph;
	adj_matrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
	std::cout << "Depth First Search  : ";
	depth_first_search(m, 0, Printer{});
	std::cout << "\n";
}

void test_toposort()
{
	using namespace graph;
	adj_matrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
	adj_matrix::vertex_list v;
	std::cout << "Topological sorted  : ";
	if (topological_sort(m, v) == false) {
		std::cout << "FAILED: circle detected";
	} else {
		for_each(v.begin(), v.end(), Printer{});
	}
	std::cout << "\n";
}

void test_edge_prop_map()
{
	using namespace graph;
	adj_matrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
	edge_property_map<float> ep(m);
	ep[{0, 1}] = 0.1;
	ep[{0, 2}] = 0.2;
	ep[{0, 3}] = 0.3;
	ep[{1, 2}] = 0.4;
	ep[{1, 3}] = 0.5;
	ep[{2, 4}] = 0.6;
	ep[{3, 4}] = 0.7;

	std::cout << "Edge Properties:\n";
	for (auto const & edge : m.edges()) {
		std::cout << "  " << edge.from << " -> " << edge.to << " : " << ep[edge] << "\n";
	}
}

void test_mst()
{
	using namespace graph;

	{
		adj_matrix m{4};
		m.add(0, 1, true, 2);
		m.add(0, 3, true, 1);
		m.add(1, 3, true, 2);
		m.add(2, 3, true, 3);

		std::cout << "Minimum Spanning Tree (Prim):\n";
		for (auto const & edge : graph::minimum_spanning_tree_prim(m)) {
			std::cout << "  " << edge.from << " -> " << edge.to << "\n";
		}
	}

	{
		adj_matrix m{6};
		m.add(0, 1, true, 1);
		m.add(0, 3, true, 4);
		m.add(0, 4, true, 3);
		m.add(1, 3, true, 4);
		m.add(1, 4, true, 2);
		m.add(2, 4, true, 4);
		m.add(2, 5, true, 5);
		m.add(3, 4, true, 4);
		m.add(4, 5, true, 7);

		std::cout << "Minimum Spanning Tree (Prim):\n";
		for (auto const & edge : graph::minimum_spanning_tree_prim(m)) {
			std::cout << "  " << edge.from << " -> " << edge.to << "\n";
		}
	}
}

void test_path()
{
	using namespace graph;
	adj_matrix m{6};
	m.add(0, 1, true, 1);
	m.add(0, 3, true, 4);
	m.add(0, 4, true, 3);
	m.add(1, 3, true, 4);
	m.add(1, 4, true, 2);
	m.add(2, 4, true, 4);
	m.add(2, 5, true, 5);
	m.add(3, 4, true, 4);
	m.add(4, 5, true, 7);

	std::cout << "Shortest Path (Dijkstra):";
	for (auto const & v : graph::shortest_path_dijkstra(m, 0, 2)) {
		std::cout << " " << v;
	}
	std::cout << "\n";
}

int main(int, char **)
{
	test_bfs();
	test_dfs();
	test_toposort();
	test_edge_prop_map();
	test_mst();
	test_path();

	return 0;
}
