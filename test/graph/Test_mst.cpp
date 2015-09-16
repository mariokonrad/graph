#include <gtest/gtest.h>
#include <graph/mst.hpp>

namespace
{
class Test_mst : public ::testing::Test
{
public:
	using el = graph::adjmatrix::edge_list_t;

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

TEST_F(Test_mst, simple_bidirectional)
{
	EXPECT_EQ((el{{-1, 0}, {0, 1}, {0, 2}, {2, 3}, {3, 4}}),
		graph::minimum_spanning_tree_prim(create_simple_bi()));
}
}
