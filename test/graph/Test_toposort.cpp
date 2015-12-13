#include <gtest/gtest.h>
#include <graph/toposort.hpp>
#include <graph/adjmatrix.hpp>

namespace
{
TEST(Test_toposort, no_cycle)
{
	graph::vertex_list v;
	bool success;
	std::tie(v, success) = graph::topological_sort(
		graph::adjmatrix{5, {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 1}, {2, 3}}});

	EXPECT_TRUE(success);
	EXPECT_EQ((graph::vertex_list{0, 2, 1, 3, 4}), v);
}

TEST(Test_toposort, cycle)
{
	graph::vertex_list v;
	bool success;
	std::tie(v, success) = graph::topological_sort(
		graph::adjmatrix{5, {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 1}, {2, 3}, {3, 1}}});

	EXPECT_FALSE(success);
	EXPECT_EQ((graph::vertex_list{}), v);
}
}
