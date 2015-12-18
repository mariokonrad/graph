#include <gtest/gtest.h>
#include <map>
#include <graph/mst.hpp>
#include <graph/adjmatrix.hpp>
#include <graph/adjlist.hpp>

namespace
{
using namespace graph;

class Test_mst : public ::testing::Test
{
public:
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

	template <class Graph> void test_bidirectional_property_map_int() const
	{
		// setup graph, specifiy bidirectional edges explicitly (compatible with
		// adjmatrix and adjlist)
		Graph g{5, {{0, 1}, {1, 0}, {0, 2}, {2, 0}, {1, 2}, {2, 1}, {1, 3}, {3, 1}, {2, 3},
					   {3, 2}, {2, 4}, {4, 2}, {3, 4}, {4, 3}}};

		// setup distances, be aware of bidirectional graphs, edges in the property map
		// are uni-directional.
		const std::map<edge, int> p{{{{0, 1}, 1}, {{1, 0}, 1}, {{0, 2}, 2}, {{2, 0}, 2},
			{{1, 2}, 2}, {{2, 1}, 2}, {{1, 3}, 3}, {{3, 1}, 3}, {{2, 3}, 1}, {{3, 2}, 1},
			{{2, 4}, 5}, {{4, 2}, 5}, {{3, 4}, 1}, {{4, 3}, 1}}};

		const edge_list expected{{vertex_invalid, 0}, {0, 1}, {0, 2}, {2, 3}, {3, 4}};

		auto const edges = minimum_spanning_tree_prim(g, p, 0);

		EXPECT_EQ(expected, edges);
	}
};

TEST_F(Test_mst, simple_bidirectional)
{
	EXPECT_EQ((edge_list{{vertex_invalid, 0}, {0, 1}, {0, 2}, {2, 3}, {3, 4}}),
		minimum_spanning_tree_prim(create_simple_bi(), 0));
}

TEST_F(Test_mst, adjmatrix_bidirectional_property_map_int)
{
	test_bidirectional_property_map_int<adjmatrix>();
}

TEST_F(Test_mst, adjlist_bidirectional_property_map_int)
{
	test_bidirectional_property_map_int<adjlist>();
}
}
