#include <gtest/gtest.h>
#include <map>
#include <unordered_map>
#include <graph/path.hpp>
#include <graph/adjmatrix.hpp>
#include <graph/adjlist.hpp>

namespace
{
using namespace graph;

class Test_path : public ::testing::Test
{
public:
	static adjmatrix create_simple_uni()
	{
		adjmatrix g{5};
		g.add(0, 1, edge::type::uni, 1);
		g.add(0, 2, edge::type::uni, 2);
		g.add(1, 2, edge::type::uni, 2);
		g.add(1, 3, edge::type::uni, 3);
		g.add(2, 3, edge::type::uni, 1);
		g.add(2, 4, edge::type::uni, 5);
		g.add(3, 4, edge::type::uni, 1);
		return g;
	}

	static adjmatrix create_cycle_uni()
	{
		adjmatrix g{5};
		g.add(0, 1, edge::type::uni, 1);
		g.add(0, 2, edge::type::uni, 2);
		g.add(1, 2, edge::type::uni, 2);
		g.add(1, 3, edge::type::uni, 3);
		g.add(2, 3, edge::type::uni, 1);
		g.add(2, 4, edge::type::uni, 5);
		g.add(3, 4, edge::type::uni, 1);
		g.add(4, 0, edge::type::uni, 4);
		g.add(3, 0, edge::type::uni, 2);
		g.add(3, 1, edge::type::uni, 1);
		return g;
	}

	static adjmatrix create_simple_bi()
	{
		adjmatrix g{5};
		g.add(0, 1, edge::type::bi, 1);
		g.add(0, 2, edge::type::bi, 2);
		g.add(1, 2, edge::type::bi, 2);
		g.add(1, 3, edge::type::bi, 3);
		g.add(2, 3, edge::type::bi, 1);
		g.add(2, 4, edge::type::bi, 5);
		g.add(3, 4, edge::type::bi, 1);
		return g;
	}

	template <class Graph> void test_distances_with_property_map_int() const
	{
		const Graph g{5,
			{{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {2, 4}, {3, 4}, {4, 0}, {3, 0}, {3, 1}}};

		const std::map<edge, int> distances{
			{{0, 1}, 1}, {{0, 2}, 2}, {{1, 2}, 2}, {{1, 3}, 3}, {{2, 3}, 1}, {{2, 4}, 5},
			{{3, 4}, 1}, {{4, 0}, 4}, {{3, 0}, 2}, {{3, 1}, 1},
		};

		vertex_list v;
		bool reachable;
		std::tie(v, reachable) = shortest_path_dijkstra(g, distances, 2, 4);

		EXPECT_TRUE(reachable);
		EXPECT_EQ((vertex_list{2, 3, 4}), v);
	}

	template <class Graph> void test_distances_with_property_map_unordered_map_int() const
	{
		const Graph g{5,
			{{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {2, 4}, {3, 4}, {4, 0}, {3, 0}, {3, 1}}};

		const std::unordered_map<edge, int, graph::edge_hash> distances{
			{{0, 1}, 1}, {{0, 2}, 2}, {{1, 2}, 2}, {{1, 3}, 3}, {{2, 3}, 1}, {{2, 4}, 5},
			{{3, 4}, 1}, {{4, 0}, 4}, {{3, 0}, 2}, {{3, 1}, 1},
		};

		vertex_list v;
		bool reachable;
		std::tie(v, reachable) = shortest_path_dijkstra(g, distances, 2, 4);

		EXPECT_TRUE(reachable);
		EXPECT_EQ((vertex_list{2, 3, 4}), v);
	}

	template <class Graph> void test_distances_with_property_map_float()
	{
		const Graph g{5,
			{{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}, {2, 4}, {3, 4}, {4, 0}, {3, 0}, {3, 1}}};

		const std::map<edge, float> distances{
			{{0, 1}, 1.0}, {{0, 2}, 2.0}, {{1, 2}, 2.0}, {{1, 3}, 3.0}, {{2, 3}, 1.0},
			{{2, 4}, 5.0}, {{3, 4}, 1.0}, {{4, 0}, 4.0}, {{3, 0}, 2.0}, {{3, 1}, 1.0},
		};

		vertex_list v;
		bool reachable;
		std::tie(v, reachable) = shortest_path_dijkstra(g, distances, 2, 4);

		EXPECT_TRUE(reachable);
		EXPECT_EQ((vertex_list{2, 3, 4}), v);
	}
};

TEST_F(Test_path, simple_bidirectional_0_3)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_simple_bi(), 0, 3);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{0, 2, 3}), v);
}

TEST_F(Test_path, simple_bidirectional_0_4)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_simple_bi(), 0, 4);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{0, 2, 3, 4}), v);
}

TEST_F(Test_path, simple_bidirectional_2_4)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_simple_bi(), 2, 4);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{2, 3, 4}), v);
}

TEST_F(Test_path, simple_unidirectional_0_3)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_simple_uni(), 0, 3);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{0, 2, 3}), v);
}

TEST_F(Test_path, simple_unidirectional_0_4)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_simple_uni(), 0, 4);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{0, 2, 3, 4}), v);
}

TEST_F(Test_path, simple_unidirectional_2_4)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_simple_uni(), 2, 4);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{2, 3, 4}), v);
}

TEST_F(Test_path, cycle_unidirectional_2_0)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_cycle_uni(), 2, 0);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{2, 3, 0}), v);
}

TEST_F(Test_path, cycle_unidirectional_3_2)
{
	vertex_list v;
	bool success;
	std::tie(v, success) = shortest_path_dijkstra(create_cycle_uni(), 3, 2);

	EXPECT_TRUE(success);
	EXPECT_EQ((vertex_list{3, 1, 2}), v);
}

TEST_F(Test_path, unreachable_destination)
{
	adjmatrix g{4, {{0, 1}, {1, 2}}}; // node 3 not reachable

	vertex_list v;
	bool reachable;
	std::tie(v, reachable) = shortest_path_dijkstra(g, 0, 3);

	EXPECT_FALSE(reachable);
	EXPECT_EQ((vertex_list{}), v);
}

TEST_F(Test_path, adjmatrix_distances_with_property_map_int)
{
	test_distances_with_property_map_int<adjmatrix>();
}

TEST_F(Test_path, adjmatrix_distances_with_property_map_unordered_map_int)
{
	test_distances_with_property_map_unordered_map_int<adjmatrix>();
}

TEST_F(Test_path, adjmatrix_distances_with_property_map_float)
{
	test_distances_with_property_map_float<adjmatrix>();
}

TEST_F(Test_path, adjlist_distances_with_property_map_int)
{
	test_distances_with_property_map_int<adjlist>();
}

TEST_F(Test_path, adjlist_distances_with_property_map_unordered_map_int)
{
	test_distances_with_property_map_unordered_map_int<adjlist>();
}

TEST_F(Test_path, adjlist_distances_with_property_map_float)
{
	test_distances_with_property_map_float<adjlist>();
}
}
