#include <gtest/gtest.h>
#include "complex_array.hpp"

TEST(ComplexArrayTests, ParameterizedConstructor)
{
  ComplexArray cmps(0, 0, 0);
  EXPECT_TRUE(cmps.empty());
  EXPECT_EQ(cmps.size(), 0);
}

TEST(ComplexArrayTests, CopyConstructor)
{
  ComplexArray cmps(10, 1, 1);
  ComplexArray clone = cmps;
  EXPECT_FALSE(clone.empty());
  EXPECT_EQ(clone.size(), cmps.size());
}

TEST(ComplexArrayTests, CopyAssigmentOperatorSufficientCapacity)
{
  ComplexArray cmps(10, 1, 1);
  ComplexArray clone(20, 0, 0);
  clone = cmps;
  EXPECT_FALSE(clone.empty());
  EXPECT_EQ(clone.size(), cmps.size());
}

TEST(ComplexArrayTests, CopyAssigmentOperatorInsufficientCapacity)
{
  ComplexArray cmps(10, 1, 1);
  ComplexArray clone(1, 0, 0);
  clone = cmps;
  EXPECT_FALSE(clone.empty());
  EXPECT_EQ(clone.size(), cmps.size());
}
