#include "pch.h"

#include <gtest/gtest.h>

#include "use_for_test.h"

TEST(UseForTest, add)
{
	UseForTest usefortest;
	EXPECT_EQ(usefortest.add(2, 3), 5);
}

TEST(UseForTest, getIpInfo)
{
	UseForTest usefortest;
	EXPECT_TRUE(usefortest.getIpInfo());
}

TEST(UseForTest, compareStructs)
{
	UseForTest usefortest;
	EXPECT_TRUE(usefortest.compareStructs());
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}