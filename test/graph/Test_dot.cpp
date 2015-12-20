#include <gtest/gtest.h>
#include <graph/dot.hpp>
#include <graph/adjmatrix.hpp>

namespace
{
TEST(Test_dot, simple)
{
	const auto s = graph::dot(graph::adjmatrix{4, {{0, 1}, {0, 2}, {1, 2}, {1, 3}, {2, 3}}});
	EXPECT_STREQ("digraph G {\n"
				 "\t0;\n"
				 "\t1;\n"
				 "\t2;\n"
				 "\t3;\n"
				 "\t0 -> 1;\n"
				 "\t0 -> 2;\n"
				 "\t1 -> 2;\n"
				 "\t1 -> 3;\n"
				 "\t2 -> 3;\n"
				 "}\n",
		s.c_str());
}
}
