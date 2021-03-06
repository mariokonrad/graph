#include <gtest/gtest.h>
#include <graph/bfs.hpp>
#include <graph/adjmatrix.hpp>
#include <graph/adjlist.hpp>

namespace
{
using namespace graph;

class Test_bfs : public ::testing::Test
{
public:
	template <class Graph> void test_empty_graph() const
	{
		const Graph g{5};
		vertex_list v;
		breadth_first_search(g, 0, [&v](auto const &, auto vertex) { v.push_back(vertex); });
		EXPECT_EQ((vertex_list{0}), v);
	}

	template <class Graph> void test_invalid_node() const
	{
		vertex_list v;
		breadth_first_search(
			Graph{5}, 5, [&v](auto const &, auto vertex) { v.push_back(vertex); });
		EXPECT_EQ((vertex_list{}), v);
	}

	template <class Graph> void test_bfs(const vertex_list & expected, vertex start) const
	{
		vertex_list v;
		breadth_first_search(Graph{5, {{0, 1}, {1, 3}, {3, 0}, {2, 3}, {2, 4}, {3, 2}, {3, 4}}},
			start, [&v](auto const &, auto vertex) { v.push_back(vertex); });
		EXPECT_EQ(expected, v);
	}
};

TEST_F(Test_bfs, adjmatrix_empty_graph) { test_empty_graph<adjmatrix>(); }

TEST_F(Test_bfs, adjmatrix_invalid_node) { test_invalid_node<adjmatrix>(); }

TEST_F(Test_bfs, adjmatrix_graph_start_0)
{
	test_bfs<adjmatrix>(vertex_list{0, 1, 3, 2, 4}, 0);
}

TEST_F(Test_bfs, adjmatrix_graph_start_1)
{
	test_bfs<adjmatrix>(vertex_list{1, 3, 0, 2, 4}, 1);
}

TEST_F(Test_bfs, adjmatrix_graph_start_2)
{
	test_bfs<adjmatrix>(vertex_list{2, 3, 4, 0, 1}, 2);
}

TEST_F(Test_bfs, adjmatrix_graph_start_3)
{
	test_bfs<adjmatrix>(vertex_list{3, 0, 2, 4, 1}, 3);
}

TEST_F(Test_bfs, adjmatrix_graph_start_4) { test_bfs<adjmatrix>(vertex_list{4}, 4); }

TEST_F(Test_bfs, adjlist_empty_graph) { test_empty_graph<adjlist>(); }

TEST_F(Test_bfs, adjlist_invalid_node) { test_invalid_node<adjlist>(); }

TEST_F(Test_bfs, adjlist_graph_start_0) { test_bfs<adjlist>(vertex_list{0, 1, 3, 2, 4}, 0); }

TEST_F(Test_bfs, adjlist_graph_start_1) { test_bfs<adjlist>(vertex_list{1, 3, 0, 2, 4}, 1); }

TEST_F(Test_bfs, adjlist_graph_start_2) { test_bfs<adjlist>(vertex_list{2, 3, 4, 0, 1}, 2); }

TEST_F(Test_bfs, adjlist_graph_start_3) { test_bfs<adjlist>(vertex_list{3, 0, 2, 4, 1}, 3); }

TEST_F(Test_bfs, adjlist_graph_start_4) { test_bfs<adjlist>(vertex_list{4}, 4); }
}
