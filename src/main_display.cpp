#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(){
  cv::Mat image;

  image = cv::imread("/Users/michaelwells/Downloads/coin-1.JPG");

  if(image.empty()){
    std::cout<< "Image is empty" << std::endl;
  }

  cv::namedWindow("Original Image");
  cv::imshow("Original Image", image);

  cv::waitKey(0);
  return 0;
}