#include <gtest/gtest.h>
#include <graph/adjmatrix.hpp>

namespace
{

TEST(Test_adjmatrix, default_construction)
{
	EXPECT_NO_THROW(graph::adjmatrix m{4});
}
}
