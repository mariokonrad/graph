#include <gtest/gtest.h>
#include <utils/priority_queue.hpp>

namespace
{

TEST(Test_utils_priority_queue, default_construction)
{
	EXPECT_NO_THROW(utils::priority_queue<int> pq);
}

TEST(Test_utils_priority_queue, default_construction_status)
{
	utils::priority_queue<int> pq;
	EXPECT_EQ(0u, pq.size());
	EXPECT_TRUE(pq.empty());
}

TEST(Test_utils_priority_queue, construction_predefined_container)
{
	std::vector<int> v{9, 0, 8, 1, 7, 2, 6, 3, 5, 4};
	utils::priority_queue<int> pq(std::less<int>{}, std::move(v));
	EXPECT_EQ(10u, pq.size());
	EXPECT_FALSE(pq.empty());
}

TEST(Test_utils_priority_queue, push)
{
	utils::priority_queue<int> pq;

	pq.push(9);
	pq.push(0);
	pq.push(1);

	EXPECT_EQ(3u, pq.size());
}

TEST(Test_utils_priority_queue, pop)
{
	utils::priority_queue<int> pq{std::less<int>{}, {9, 0, 1, 8}};

	EXPECT_EQ(4u, pq.size());

	EXPECT_EQ(9, pq.top());
	pq.pop();
	EXPECT_EQ(3u, pq.size());

	EXPECT_EQ(8, pq.top());
	pq.pop();
	EXPECT_EQ(2u, pq.size());

	EXPECT_EQ(1, pq.top());
	pq.pop();
	EXPECT_EQ(1u, pq.size());

	EXPECT_EQ(0, pq.top());
	pq.pop();
	EXPECT_EQ(0u, pq.size());
}

TEST(Test_utils_priority_queue, find_if)
{
	utils::priority_queue<int> pq;

	pq.push(9);
	pq.push(0);
	pq.push(1);
	pq.push(8);

	EXPECT_EQ(std::begin(pq) + 3u,
		find_if(std::begin(pq), std::end(pq), [](int value) { return value == 0; }));
	EXPECT_EQ(std::begin(pq) + 2u,
		find_if(std::begin(pq), std::end(pq), [](int value) { return value == 1; }));
	EXPECT_EQ(std::begin(pq) + 1u,
		find_if(std::begin(pq), std::end(pq), [](int value) { return value == 8; }));
	EXPECT_EQ(std::begin(pq) + 0u,
		find_if(std::begin(pq), std::end(pq), [](int value) { return value == 9; }));
}

TEST(Test_utils_priority_queue, update)
{
	utils::priority_queue<int> pq;

	pq.push(3);
	pq.push(0);
	pq.push(1);
	pq.push(2);

	auto i = find_if(std::begin(pq), std::end(pq), [](int value) { return value == 2; });
	pq.update(i, 4);

	EXPECT_EQ(4u, pq.size());

	EXPECT_EQ(4, pq.top());
	pq.pop();
	EXPECT_EQ(3u, pq.size());

	EXPECT_EQ(3, pq.top());
	pq.pop();
	EXPECT_EQ(2u, pq.size());

	EXPECT_EQ(1, pq.top());
	pq.pop();
	EXPECT_EQ(1u, pq.size());

	EXPECT_EQ(0, pq.top());
	pq.pop();
	EXPECT_EQ(0u, pq.size());
}
}
