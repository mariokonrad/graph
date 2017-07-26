#include <graph/graph.hpp>
#include <graph/adjmatrix.hpp>
#include <graph/adjlist.hpp>
#include <gtest/gtest.h>

namespace
{
TEST(Test_graph, outgoing)
{
	{
		const graph::adjmatrix m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};
		EXPECT_EQ(3u, outgoing(m, 0).size());
		EXPECT_EQ(2u, outgoing(m, 1).size());
		EXPECT_EQ(0u, outgoing(m, 2).size());
		EXPECT_EQ(0u, outgoing(m, 3).size());
	}
	{
		const graph::adjlist m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};
		EXPECT_EQ(3u, outgoing(m, 0).size());
		EXPECT_EQ(2u, outgoing(m, 1).size());
		EXPECT_EQ(0u, outgoing(m, 2).size());
		EXPECT_EQ(0u, outgoing(m, 3).size());
	}
}

TEST(Test_graph, incoming)
{
	const graph::adjmatrix m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};

	EXPECT_EQ(1u, incoming(m, 0).size());
	EXPECT_EQ(1u, incoming(m, 1).size());
	EXPECT_EQ(2u, incoming(m, 2).size());
	EXPECT_EQ(1u, incoming(m, 3).size());
}
}
