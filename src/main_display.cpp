#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(){
  cv::Mat image;

  image = cv::imread("images/coin-1.JPG");

  if(image.empty()){
    std::cout<< "Image is empty" << std::endl;
  }

  cv::namedWindow("Original Image");
  cv::imshow("Original Image", image);

  cv::Mat result;
  cv::flip(image, result, 1);

  cv::namedWindow("Output Image");
  cv::imshow("Output Image", result);

  cv::waitKey(0);
  return 0;
}