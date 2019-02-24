#include <gtest/gtest.h>
#include <map>
#include <iostream>
#include "histogram.hpp"

TEST(Histogram, VectorOfChars){
  const std::string str = "Hello World!";
  std::vector<char> values(str.begin(), str.end());
  auto hist = histogram(values);

  ASSERT_EQ(hist['H'], 1);
  ASSERT_EQ(hist['l'], 3); 
}

TEST(Histogram, VectorOfInts){
  std::vector<int> values { 1, 1, 2, 2, 3 };
  auto hist = histogram(values);

  ASSERT_EQ(hist[1], 2);
  ASSERT_EQ(hist[2], 2);
  ASSERT_EQ(hist[3], 1);
}