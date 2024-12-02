#include <gtest/gtest.h>
#include "../complex_array.hpp"

void ExpectEqualAll(const ComplexArray& cmps, double re, double im)
{
  for (size_t i = 0; i < cmps.size(); ++i) {
    EXPECT_EQ(cmps.real_at(i), re) << "Mismatch at " << i << " index";
    EXPECT_EQ(cmps.imag_at(i), im) << "Mismatch at " << i << " index";
  }
}

TEST(ComplexArrayTests, EmptyConstructor)
{
  ComplexArray cmps(0, 0, 0);
  EXPECT_TRUE(cmps.empty());
  EXPECT_EQ(cmps.size(), 0);
}

TEST(ComplexArrayTests, ParameterizedConstructor)
{
  ComplexArray cmps(10, 0.5, 0.7);
  EXPECT_FALSE(cmps.empty());
  EXPECT_EQ(cmps.size(), 10);
  ExpectEqualAll(cmps, 0.5, 0.7);
}

TEST(ComplexArrayTests, CopyConstructor)
{
  ComplexArray cmps(10, 1, 1);
  ComplexArray clone = cmps;
  EXPECT_FALSE(clone.empty());
  EXPECT_EQ(clone.size(), cmps.size());
  ExpectEqualAll(clone, 1, 1);
}

TEST(ComplexArrayTests, CopyAssigmentOperatorSufficientCapacity)
{
  ComplexArray cmps(10, 1, 1);
  ComplexArray clone(20, 0, 0);
  clone = cmps;
  EXPECT_FALSE(clone.empty());
  EXPECT_EQ(clone.size(), cmps.size());
  ExpectEqualAll(clone, 1, 1);
}

TEST(ComplexArrayTests, CopyAssigmentOperatorInsufficientCapacity)
{
  ComplexArray cmps(10, 1, 1);
  ComplexArray clone(1, 0, 0);
  clone = cmps;
  EXPECT_FALSE(clone.empty());
  EXPECT_EQ(clone.size(), cmps.size());
  ExpectEqualAll(clone, 1, 1);
}

TEST(ComplexArrayTests, ResizeSameSize)
{
  ComplexArray cmps(5, 1.0, 1.0);
  cmps.resize(5, 2.0, 2.0);
  EXPECT_EQ(cmps.size(), 5);
  ExpectEqualAll(cmps, 1, 1);
}

TEST(ComplexArrayTests, ResizeShrink)
{
  ComplexArray cmps(10, 1.0, 1.0);
  cmps.resize(5, 0.0, 0.0);
  EXPECT_EQ(cmps.size(), 5);
  ExpectEqualAll(cmps, 1, 1);
}

TEST(ComplexArrayTests, ResizeExpandSufficientCapacity)
{
  ComplexArray cmps(5, 1.0, 1.0);
  cmps.resize(10, 2.0, 2.0);

  EXPECT_EQ(cmps.size(), 10);
  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(cmps.real_at(i), 1.0);
    EXPECT_EQ(cmps.imag_at(i), 1.0);
  }
  for (size_t i = 5; i < 10; ++i) {
    EXPECT_EQ(cmps.real_at(i), 2.0);
    EXPECT_EQ(cmps.imag_at(i), 2.0);
  }
}

TEST(ComplexArrayTests, ResizeExpandInsufficientCapacity)
{
  ComplexArray cmps(5, 1.0, 1.0);
  cmps.resize(20, 3.0, 3.0);

  EXPECT_EQ(cmps.size(), 20);
  for (size_t i = 0; i != 5; ++i) {
    EXPECT_EQ(cmps.real_at(i), 1.0);
    EXPECT_EQ(cmps.imag_at(i), 1.0);
  }
  for (size_t i = 5; i != 20; ++i) {
    EXPECT_EQ(cmps.real_at(i), 3.0);
    EXPECT_EQ(cmps.imag_at(i), 3.0);
  }
}

