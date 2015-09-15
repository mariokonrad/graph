#include <gtest/gtest.h>
#include <graph/bfs.hpp>

namespace
{
class Test_bfs : public ::testing::Test
{
public:
	static graph::adjmatrix create_graph()
	{
		return graph::adjmatrix{5, {{0, 1}, {1, 3}, {3, 0}, {2, 3}, {2, 4}, {3, 2}, {3, 4}}};
	}

	void test_bfs(const graph::adjmatrix::vertex_list_t & expected,
		graph::adjmatrix::vertex_t start) const
	{
		graph::adjmatrix::vertex_list_t v;
		graph::breadth_first_search(
			create_graph(), start, [&v](auto vertex) { v.push_back(vertex); });
		EXPECT_EQ(expected, v);
	}
};

TEST_F(Test_bfs, empty_graph)
{
	const graph::adjmatrix g{5};
	graph::adjmatrix::vertex_list_t v;
	graph::breadth_first_search(g, 0, [&v](auto vertex) { v.push_back(vertex); });
	EXPECT_EQ((graph::adjmatrix::vertex_list_t{0}), v);
}

TEST_F(Test_bfs, invalid_node)
{
	graph::adjmatrix::vertex_list_t v;
	graph::breadth_first_search(
		graph::adjmatrix{5}, 5, [&v](auto vertex) { v.push_back(vertex); });
	EXPECT_EQ((graph::adjmatrix::vertex_list_t{}), v);
}

TEST_F(Test_bfs, graph_start_0) { test_bfs(graph::adjmatrix::vertex_list_t{0, 1, 3, 2, 4}, 0); }

TEST_F(Test_bfs, graph_start_1) { test_bfs(graph::adjmatrix::vertex_list_t{1, 3, 0, 2, 4}, 1); }

TEST_F(Test_bfs, graph_start_2) { test_bfs(graph::adjmatrix::vertex_list_t{2, 3, 4, 0, 1}, 2); }

TEST_F(Test_bfs, graph_start_3) { test_bfs(graph::adjmatrix::vertex_list_t{3, 0, 2, 4, 1}, 3); }

TEST_F(Test_bfs, graph_start_4) { test_bfs(graph::adjmatrix::vertex_list_t{4}, 4); }
}
