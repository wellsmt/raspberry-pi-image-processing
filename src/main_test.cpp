#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/hal/interface.h>

TEST(OpenCV_Serialization, Serialize)
{
  cv::Mat image;
  uint16_t rows = 480;
  uint16_t cols = 640;
  image.create(rows, cols, CV_8U);
  image.at<double>(0,0) = 1;
  
  ASSERT_EQ(image.at<double>(0,0), 1);
  ASSERT_EQ(image.channels(), 1);
  ASSERT_EQ(image.depth(), 0);
  ASSERT_EQ(true, true);
}
