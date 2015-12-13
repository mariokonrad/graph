#include <gtest/gtest.h>
#include <map>
#include <graph/mst.hpp>
#include <graph/adjmatrix.hpp>

namespace
{
class Test_mst : public ::testing::Test
{
public:
	using el = graph::edge_list;

	static graph::adjmatrix create_simple_bi()
	{
		graph::adjmatrix g{5};
		g.add(0, 1, graph::edge::type::bi, 1);
		g.add(0, 2, graph::edge::type::bi, 2);
		g.add(1, 2, graph::edge::type::bi, 2);
		g.add(1, 3, graph::edge::type::bi, 3);
		g.add(2, 3, graph::edge::type::bi, 1);
		g.add(2, 4, graph::edge::type::bi, 5);
		g.add(3, 4, graph::edge::type::bi, 1);
		return g;
	}
};

TEST_F(Test_mst, simple_bidirectional)
{
	EXPECT_EQ((el{{graph::vertex_invalid, 0}, {0, 1}, {0, 2}, {2, 3}, {3, 4}}),
		graph::minimum_spanning_tree_prim(create_simple_bi()));
}

TEST_F(Test_mst, bidirectional_property_map_int)
{
	// setup graph
	graph::adjmatrix g{5};
	g.add(0, 1, graph::edge::type::bi);
	g.add(0, 2, graph::edge::type::bi);
	g.add(1, 2, graph::edge::type::bi);
	g.add(1, 3, graph::edge::type::bi);
	g.add(2, 3, graph::edge::type::bi);
	g.add(2, 4, graph::edge::type::bi);
	g.add(3, 4, graph::edge::type::bi);

	// setup distances, be aware of bidirectional graphs, edges in the property map
	// are uni-directional.
	const std::map<graph::edge, int> p{{{{0, 1}, 1}, {{1, 0}, 1}, {{0, 2}, 2}, {{2, 0}, 2},
		{{1, 2}, 2}, {{2, 1}, 2}, {{1, 3}, 3}, {{3, 1}, 3}, {{2, 3}, 1}, {{3, 2}, 1},
		{{2, 4}, 5}, {{4, 2}, 5}, {{3, 4}, 1}, {{4, 3}, 1}}};

	const graph::edge_list expected{{graph::vertex_invalid, 0}, {0, 1}, {0, 2}, {2, 3}, {3, 4}};

	auto const edges = graph::minimum_spanning_tree_prim(g, p);

	EXPECT_EQ(expected, edges);
}
}
