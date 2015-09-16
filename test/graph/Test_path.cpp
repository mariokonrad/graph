#include <gtest/gtest.h>
#include <graph/path.hpp>

namespace
{
using namespace graph;
using vl = adjmatrix::vertex_list_t;

class Test_path : public ::testing::Test
{
public:
	static adjmatrix create_simple_uni()
	{
		adjmatrix g{5};
		g.add(0, 1, adjmatrix::edge_type::uni, 1);
		g.add(0, 2, adjmatrix::edge_type::uni, 2);
		g.add(1, 2, adjmatrix::edge_type::uni, 2);
		g.add(1, 3, adjmatrix::edge_type::uni, 3);
		g.add(2, 3, adjmatrix::edge_type::uni, 1);
		g.add(2, 4, adjmatrix::edge_type::uni, 5);
		g.add(3, 4, adjmatrix::edge_type::uni, 1);
		return g;
	}

	static adjmatrix create_cycle_uni()
	{
		adjmatrix g{5};
		g.add(0, 1, adjmatrix::edge_type::uni, 1);
		g.add(0, 2, adjmatrix::edge_type::uni, 2);
		g.add(1, 2, adjmatrix::edge_type::uni, 2);
		g.add(1, 3, adjmatrix::edge_type::uni, 3);
		g.add(2, 3, adjmatrix::edge_type::uni, 1);
		g.add(2, 4, adjmatrix::edge_type::uni, 5);
		g.add(3, 4, adjmatrix::edge_type::uni, 1);
		g.add(4, 0, adjmatrix::edge_type::uni, 4);
		g.add(3, 0, adjmatrix::edge_type::uni, 2);
		g.add(3, 1, adjmatrix::edge_type::uni, 1);
		return g;
	}

	static adjmatrix create_simple_bi()
	{
		adjmatrix g{5};
		g.add(0, 1, adjmatrix::edge_type::bi, 1);
		g.add(0, 2, adjmatrix::edge_type::bi, 2);
		g.add(1, 2, adjmatrix::edge_type::bi, 2);
		g.add(1, 3, adjmatrix::edge_type::bi, 3);
		g.add(2, 3, adjmatrix::edge_type::bi, 1);
		g.add(2, 4, adjmatrix::edge_type::bi, 5);
		g.add(3, 4, adjmatrix::edge_type::bi, 1);
		return g;
	}
};

TEST_F(Test_path, simple_bidirectional_0_3)
{
	EXPECT_EQ((vl{0, 2, 3}), std::get<0>(shortest_path_dijkstra(create_simple_bi(), 0, 3)));
}

TEST_F(Test_path, simple_bidirectional_0_4)
{
	EXPECT_EQ((vl{0, 2, 3, 4}), std::get<0>(shortest_path_dijkstra(create_simple_bi(), 0, 4)));
}

TEST_F(Test_path, simple_bidirectional_2_4)
{
	EXPECT_EQ((vl{2, 3, 4}), std::get<0>(shortest_path_dijkstra(create_simple_bi(), 2, 4)));
}

TEST_F(Test_path, simple_unidirectional_0_3)
{
	EXPECT_EQ((vl{0, 2, 3}), std::get<0>(shortest_path_dijkstra(create_simple_uni(), 0, 3)));
}

TEST_F(Test_path, simple_unidirectional_0_4)
{
	EXPECT_EQ((vl{0, 2, 3, 4}), std::get<0>(shortest_path_dijkstra(create_simple_uni(), 0, 4)));
}

TEST_F(Test_path, simple_unidirectional_2_4)
{
	EXPECT_EQ((vl{2, 3, 4}), std::get<0>(shortest_path_dijkstra(create_simple_uni(), 2, 4)));
}

TEST_F(Test_path, cycle_unidirectional_2_0)
{
	EXPECT_EQ((vl{2, 3, 0}), std::get<0>(shortest_path_dijkstra(create_cycle_uni(), 2, 0)));
}

TEST_F(Test_path, cycle_unidirectional_3_2)
{
	EXPECT_EQ((vl{3, 1, 2}), std::get<0>(shortest_path_dijkstra(create_cycle_uni(), 3, 2)));
}

TEST_F(Test_path, unreachable_destination)
{
	adjmatrix g{4, {{0, 1}, {1, 2}}}; // node 3 not reachable

	adjmatrix::vertex_list_t v;
	bool reachable;
	std::tie(v, reachable) = shortest_path_dijkstra(g, 0, 3);

	EXPECT_FALSE(reachable);
	EXPECT_EQ((adjmatrix::vertex_list_t{}), v);
}
}
