#include <gtest/gtest.h>
#include <graph/dfs.hpp>

namespace
{
class Test_dfs : public ::testing::Test
{
public:
	static graph::adjmatrix create_graph()
	{
		return graph::adjmatrix{5, {{0, 1}, {1, 3}, {3, 0}, {2, 3}, {2, 4}, {3, 2}, {3, 4}}};
	}

	void test_dfs(const graph::adjmatrix::vertex_list & expected, graph::vertex start) const
	{
		graph::adjmatrix::vertex_list v;
		graph::depth_first_search(
			create_graph(), start, [&v](auto const &, auto vertex) { v.push_back(vertex); });
		EXPECT_EQ(expected, v);
	}
};

TEST_F(Test_dfs, empty_graph)
{
	const graph::adjmatrix g{5};
	graph::adjmatrix::vertex_list v;
	graph::depth_first_search(g, 0, [&v](auto const &, auto vertex) { v.push_back(vertex); });
	EXPECT_EQ((graph::adjmatrix::vertex_list{0}), v);
}

TEST_F(Test_dfs, invalid_node)
{
	graph::adjmatrix::vertex_list v;
	graph::depth_first_search(
		graph::adjmatrix{5}, 5, [&v](auto const &, auto vertex) { v.push_back(vertex); });
	EXPECT_EQ((graph::adjmatrix::vertex_list{}), v);
}

TEST_F(Test_dfs, graph_start_0) { test_dfs(graph::adjmatrix::vertex_list{0, 1, 3, 2, 4}, 0); }

TEST_F(Test_dfs, graph_start_1) { test_dfs(graph::adjmatrix::vertex_list{1, 3, 0, 2, 4}, 1); }

TEST_F(Test_dfs, graph_start_2) { test_dfs(graph::adjmatrix::vertex_list{2, 3, 0, 1, 4}, 2); }

TEST_F(Test_dfs, graph_start_3) { test_dfs(graph::adjmatrix::vertex_list{3, 0, 1, 2, 4}, 3); }

TEST_F(Test_dfs, graph_start_4) { test_dfs(graph::adjmatrix::vertex_list{4}, 4); }
}
