#include <iostream>
#include <algorithm>
#include <graph/adjmatrix.hpp>
#include <graph/dfs.hpp>
#include <graph/toposort.hpp>
#include <graph/bfs.hpp>
#include <graph/mst.hpp>
#include <graph/path.hpp>
#include <graph/property_map.hpp>

void test_bfs()
{
	using namespace graph;
	adjmatrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
	std::cout << "Breadth First Search: ";
	breadth_first_search(m, 0, [](auto const & v){ std::cout << " " << v; });
	std::cout << "\n";
}

void test_dfs()
{
	using namespace graph;
	adjmatrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
	std::cout << "Depth First Search  : ";
	depth_first_search(m, 0, [](auto const & v) { std::cout << " " << v; });
	std::cout << "\n";
}

void test_toposort()
{
	using namespace graph;
	adjmatrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
	adjmatrix::vertex_list_t v;
	bool success;
	std::tie(v, success) = topological_sort(m);
	std::cout << "Topological sorted  : ";
	if (!success) {
		std::cout << "FAILED: circle detected";
	} else {
		for_each(v.begin(), v.end(), [](auto const & v) { std::cout << " " << v; });
	}
	std::cout << "\n";
}

void test_edge_prop_map()
{
	using namespace graph;
	adjmatrix m(5, {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}, {2, 4}, {3, 4}});
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
		adjmatrix m{4};
		m.add(0, 1, adjmatrix::edge_type::bi, 2);
		m.add(0, 3, adjmatrix::edge_type::bi, 1);
		m.add(1, 3, adjmatrix::edge_type::bi, 2);
		m.add(2, 3, adjmatrix::edge_type::bi, 3);

		std::cout << "Minimum Spanning Tree (Prim):\n";
		for (auto const & edge : minimum_spanning_tree_prim(m)) {
			std::cout << "  " << edge.from << " -> " << edge.to << "\n";
		}
	}

	{
		adjmatrix m{6};
		m.add(0, 1, adjmatrix::edge_type::bi, 1);
		m.add(0, 3, adjmatrix::edge_type::bi, 4);
		m.add(0, 4, adjmatrix::edge_type::bi, 3);
		m.add(1, 3, adjmatrix::edge_type::bi, 4);
		m.add(1, 4, adjmatrix::edge_type::bi, 2);
		m.add(2, 4, adjmatrix::edge_type::bi, 4);
		m.add(2, 5, adjmatrix::edge_type::bi, 5);
		m.add(3, 4, adjmatrix::edge_type::bi, 4);
		m.add(4, 5, adjmatrix::edge_type::bi, 7);

		std::cout << "Minimum Spanning Tree (Prim):\n";
		for (auto const & edge : minimum_spanning_tree_prim(m)) {
			std::cout << "  " << edge.from << " -> " << edge.to << "\n";
		}
	}
}

void test_path()
{
	using namespace graph;
	adjmatrix m{6};
	m.add(0, 1, adjmatrix::edge_type::bi, 1);
	m.add(0, 3, adjmatrix::edge_type::bi, 4);
	m.add(0, 4, adjmatrix::edge_type::bi, 3);
	m.add(1, 3, adjmatrix::edge_type::bi, 4);
	m.add(1, 4, adjmatrix::edge_type::bi, 2);
	m.add(2, 4, adjmatrix::edge_type::bi, 4);
	m.add(2, 5, adjmatrix::edge_type::bi, 5);
	m.add(3, 4, adjmatrix::edge_type::bi, 4);
	m.add(4, 5, adjmatrix::edge_type::bi, 7);

	std::cout << "Shortest Path (Dijkstra):";
	for (auto const & v : std::get<0>(shortest_path_dijkstra(m, 0, 2))) {
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
