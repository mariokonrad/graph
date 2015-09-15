#include <gtest/gtest.h>
#include <graph/path.hpp>

namespace
{
using vl = graph::adjmatrix::vertex_list_t;

class Test_path : public ::testing::Test
{
public:
	static graph::adjmatrix create_simple_uni()
	{
		graph::adjmatrix g{5};
		g.add(0, 1, graph::adjmatrix::edge_type::uni, 1);
		g.add(0, 2, graph::adjmatrix::edge_type::uni, 2);
		g.add(1, 2, graph::adjmatrix::edge_type::uni, 2);
		g.add(1, 3, graph::adjmatrix::edge_type::uni, 3);
		g.add(2, 3, graph::adjmatrix::edge_type::uni, 1);
		g.add(2, 4, graph::adjmatrix::edge_type::uni, 5);
		g.add(3, 4, graph::adjmatrix::edge_type::uni, 1);
		return g;
	}

	static graph::adjmatrix create_cycle_uni()
	{
		graph::adjmatrix g{5};
		g.add(0, 1, graph::adjmatrix::edge_type::uni, 1);
		g.add(0, 2, graph::adjmatrix::edge_type::uni, 2);
		g.add(1, 2, graph::adjmatrix::edge_type::uni, 2);
		g.add(1, 3, graph::adjmatrix::edge_type::uni, 3);
		g.add(2, 3, graph::adjmatrix::edge_type::uni, 1);
		g.add(2, 4, graph::adjmatrix::edge_type::uni, 5);
		g.add(3, 4, graph::adjmatrix::edge_type::uni, 1);
		g.add(4, 0, graph::adjmatrix::edge_type::uni, 4);
		g.add(3, 0, graph::adjmatrix::edge_type::uni, 2);
		g.add(3, 1, graph::adjmatrix::edge_type::uni, 1);
		return g;
	}

	static graph::adjmatrix create_simple_bi()
	{
		graph::adjmatrix g{5};
		g.add(0, 1, graph::adjmatrix::edge_type::bi, 1);
		g.add(0, 2, graph::adjmatrix::edge_type::bi, 2);
		g.add(1, 2, graph::adjmatrix::edge_type::bi, 2);
		g.add(1, 3, graph::adjmatrix::edge_type::bi, 3);
		g.add(2, 3, graph::adjmatrix::edge_type::bi, 1);
		g.add(2, 4, graph::adjmatrix::edge_type::bi, 5);
		g.add(3, 4, graph::adjmatrix::edge_type::bi, 1);
		return g;
	}
};

TEST_F(Test_path, simple_bidirectional_0_3)
{
	EXPECT_EQ((vl{0, 2, 3}), graph::shortest_path_dijkstra(create_simple_bi(), 0, 3));
}

TEST_F(Test_path, simple_bidirectional_0_4)
{
	EXPECT_EQ((vl{0, 2, 3, 4}), graph::shortest_path_dijkstra(create_simple_bi(), 0, 4));
}

TEST_F(Test_path, simple_bidirectional_2_4)
{
	EXPECT_EQ((vl{2, 3, 4}), graph::shortest_path_dijkstra(create_simple_bi(), 2, 4));
}

TEST_F(Test_path, simple_unidirectional_0_3)
{
	EXPECT_EQ((vl{0, 2, 3}), graph::shortest_path_dijkstra(create_simple_uni(), 0, 3));
}

TEST_F(Test_path, simple_unidirectional_0_4)
{
	EXPECT_EQ((vl{0, 2, 3, 4}), graph::shortest_path_dijkstra(create_simple_uni(), 0, 4));
}

TEST_F(Test_path, simple_unidirectional_2_4)
{
	EXPECT_EQ((vl{2, 3, 4}), graph::shortest_path_dijkstra(create_simple_uni(), 2, 4));
}

TEST_F(Test_path, cycle_unidirectional_2_0)
{
	EXPECT_EQ((vl{2, 3, 0}), graph::shortest_path_dijkstra(create_cycle_uni(), 2, 0));
}

TEST_F(Test_path, cycle_unidirectional_3_2)
{
	EXPECT_EQ((vl{3, 1, 2}), graph::shortest_path_dijkstra(create_cycle_uni(), 3, 2));
}

}
