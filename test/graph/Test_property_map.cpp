#include <gtest/gtest.h>
#include <graph/property_map.hpp>

namespace
{
TEST(Test_property_map, vertex_map_int__access_valid_vertex)
{
	graph::adjmatrix m{4, {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}}};
	graph::vertex_property_map<int> pm{m};
	const graph::vertex_property_map<int> & cpm = pm;

	pm[0] = 0;

	EXPECT_NO_THROW(pm.prop(0) = 0);
	EXPECT_NO_THROW(cpm.prop(0));
}

TEST(Test_property_map, vertex_map_int__access_invalid_vertex)
{
	graph::adjmatrix m{4, {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}}};
	graph::vertex_property_map<int> pm{m};
	const graph::vertex_property_map<int> & cpm = pm;

	EXPECT_ANY_THROW(pm.prop(5) = 0);
	EXPECT_ANY_THROW(cpm.prop(0));
}

TEST(Test_property_map, vertex_map_int__collect_if)
{
	graph::adjmatrix m{4, {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}}};
	graph::vertex_property_map<int> pm{m};
	for (int i = 0; i < m.size(); ++i)
		pm[i] = i;

	const auto container = pm.collect_if([](auto const v) { return v % 2 == 0; });

	EXPECT_EQ(2u, container.size());
	EXPECT_EQ((graph::adjmatrix::vertex_list{0, 2}), container);
}
}
