#include <gtest/gtest.h>
#include <graph/toposort.hpp>
#include <graph/adjmatrix.hpp>
#include <graph/adjlist.hpp>

namespace
{
using namespace graph;

class Test_toposort : public ::testing::Test
{
public:
	template <class Graph> void test_no_cycle() const
	{
		vertex_list v;
		bool success;
		std::tie(v, success)
			= topological_sort(Graph{5, {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 1}, {2, 3}}});

		EXPECT_TRUE(success);
		EXPECT_EQ((vertex_list{0, 2, 1, 3, 4}), v);
	}

	template <class Graph> void test_cycle() const
	{
		vertex_list v;
		bool success;
		std::tie(v, success) = topological_sort(
			Graph{5, {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 1}, {2, 3}, {3, 1}}});

		EXPECT_FALSE(success);
		EXPECT_EQ((vertex_list{}), v);
	}
};

TEST_F(Test_toposort, adjmatrix_no_cycle) { test_no_cycle<adjmatrix>(); }

TEST_F(Test_toposort, adjmatrix_cycle) { test_cycle<adjmatrix>(); }

TEST_F(Test_toposort, adjlist_no_cycle) { test_no_cycle<adjlist>(); }

TEST_F(Test_toposort, adjlist_cycle) { test_cycle<adjlist>(); }
}
