#include "../include/bigInt.hpp"

#include <gtest/gtest.h>

TEST(BigIntegerTest, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(BigInteger A("989890097097060"));
}

// Demonstrate some basic assertions.
TEST(BigIntegerTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

// TEST(BigIntegerTest, CreatingObjectFromAnInputString) 
// {
//     BigInteger A("989890097097060");
//     A.
//     EXPECT_EQ(, "0");
//     EXPECT_EQ(bigInt.toString(), "0");
// }