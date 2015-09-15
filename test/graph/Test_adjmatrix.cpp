#include <gtest/gtest.h>
#include <graph/adjmatrix.hpp>

namespace
{

TEST(Test_adjmatrix, default_construction) { EXPECT_NO_THROW(graph::adjmatrix m{4}); }

TEST(Test_adjmatrix, default_construction_status)
{
	const graph::adjmatrix m{4};
	EXPECT_EQ(4, m.size());
	EXPECT_EQ(0, m.count_edges());
}

TEST(Test_adjmatrix, construction_initializer_list)
{
	const graph::adjmatrix m{4, {{0, 1}, {0, 2}, {1, 3}}};
	EXPECT_EQ(4, m.size());
	EXPECT_EQ(3, m.count_edges());
}

TEST(Test_adjmatrix, add_edges)
{
	graph::adjmatrix m{4};

	EXPECT_EQ(0, m.count_edges());
	m.add(0, 1);
	EXPECT_EQ(1, m.count_edges());
	m.add(1, 2);
	EXPECT_EQ(2, m.count_edges());
	m.add(2, 3);
	EXPECT_EQ(3, m.count_edges());
}

TEST(Test_adjmatrix, add_edges_out_of_range)
{
	graph::adjmatrix m{4};

	EXPECT_FALSE(m.add(0, 4));
	EXPECT_FALSE(m.add(4, 0));
}

TEST(Test_adjmatrix, add_edges_bidirectional)
{
	graph::adjmatrix m{2};

	EXPECT_TRUE(m.add(0, 1, true));
	EXPECT_EQ(2, m.count_edges());
}

TEST(Test_adjmatrix, neighbors_of)
{
	graph::adjmatrix m{4};

	m.add(0, 1);
	m.add(0, 2);
	m.add(0, 3);
	m.add(1, 0);
	m.add(1, 2);

	EXPECT_EQ(3u, m.neighbors_of(0).size());
	EXPECT_EQ(2u, m.neighbors_of(1).size());
	EXPECT_EQ(0u, m.neighbors_of(2).size());
	EXPECT_EQ(0u, m.neighbors_of(3).size());
}

TEST(Test_adjmatrix, incoming)
{
	graph::adjmatrix m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};

	EXPECT_EQ(1u, m.incoming(0).size());
	EXPECT_EQ(1u, m.incoming(1).size());
	EXPECT_EQ(2u, m.incoming(2).size());
	EXPECT_EQ(1u, m.incoming(3).size());
}

TEST(Test_adjmatrix, outgoing)
{
	graph::adjmatrix m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};

	EXPECT_EQ(3u, m.outgoing(0).size());
	EXPECT_EQ(2u, m.outgoing(1).size());
	EXPECT_EQ(0u, m.outgoing(2).size());
	EXPECT_EQ(0u, m.outgoing(3).size());
}

TEST(Test_adjmatrix, remove)
{
	graph::adjmatrix m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};

	EXPECT_EQ(4, m.size());
	EXPECT_EQ(5, m.count_edges());

	m.remove({0,1});

	EXPECT_EQ(4, m.size());
	EXPECT_EQ(4, m.count_edges());
}
}
