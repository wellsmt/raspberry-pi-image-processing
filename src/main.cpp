#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

int main(){
  cv::Mat image;

  image = cv::imread("images/coin-1.JPG");

  if(image.empty()){
    std::cout<< "Image is empty" << std::endl;
  }

  cv::Mat result;
  cv::flip(image, result, 1);

  cv::imwrite("coin-flip-1.jpg", result);
  return 0;
}
