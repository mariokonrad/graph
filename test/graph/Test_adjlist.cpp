#include <gtest/gtest.h>
#include <graph/adjlist.hpp>

namespace
{

TEST(Test_adjlist, default_construction) { EXPECT_NO_THROW(graph::adjlist g{4}); }

TEST(Test_adjlist, default_construction_status)
{
	const graph::adjlist g{4};
	EXPECT_EQ(4u, g.size());
	EXPECT_EQ(0u, g.count_edges());
}

TEST(Test_adjlist, construction_initializer_list)
{
	const graph::adjlist g{4, {{0, 1}, {0, 2}, {1, 3}}};
	EXPECT_EQ(4u, g.size());
	EXPECT_EQ(3u, g.count_edges());
}

TEST(Test_adjlist, add_edges)
{
	graph::adjlist m{4};

	EXPECT_EQ(0u, m.count_edges());
	m.add(0, 1);
	EXPECT_EQ(1u, m.count_edges());
	m.add(1, 2);
	EXPECT_EQ(2u, m.count_edges());
	m.add(2, 3);
	EXPECT_EQ(3u, m.count_edges());
}

TEST(Test_adjlist, add_edges_out_of_range)
{
	graph::adjlist m{4};

	EXPECT_FALSE(m.add(0, 4));
	EXPECT_FALSE(m.add(4, 0));
}

TEST(Test_adjlist, add_edges_bidirectional)
{
	graph::adjlist m{2};

	EXPECT_TRUE(m.add(0, 1, graph::edge::type::bi));
	EXPECT_EQ(2u, m.count_edges());
}

TEST(Test_adjlist, incoming)
{
	graph::adjlist m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};

	EXPECT_EQ(1u, m.incoming(0).size());
	EXPECT_EQ(1u, m.incoming(1).size());
	EXPECT_EQ(2u, m.incoming(2).size());
	EXPECT_EQ(1u, m.incoming(3).size());
}

TEST(Test_adjlist, outgoing)
{
	graph::adjlist m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};

	EXPECT_EQ(3u, m.outgoing(0).size());
	EXPECT_EQ(2u, m.outgoing(1).size());
	EXPECT_EQ(0u, m.outgoing(2).size());
	EXPECT_EQ(0u, m.outgoing(3).size());
}

TEST(Test_adjlist, remove)
{
	graph::adjlist m{4, {{0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 2}}};

	EXPECT_EQ(4u, m.size());
	EXPECT_EQ(5u, m.count_edges());

	m.remove({0, 1});

	EXPECT_EQ(4u, m.size());
	EXPECT_EQ(4u, m.count_edges());
}

TEST(Test_adjlist, vertices)
{
	graph::adjlist m{4};

	const auto v = m.vertices();

	EXPECT_EQ((graph::vertex_list{0, 1, 2, 3}), v);
}
}
