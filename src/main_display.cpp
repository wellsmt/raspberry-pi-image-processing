#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

void onMouse(int event, int x, int y, int flags, void* param)
{
  cv::Mat *im = reinterpret_cast<cv::Mat*>(param);
  switch(event)
  {
    case cv::EVENT_LBUTTONDOWN:
      std::cout << "at (" << x << "," << y << ") value is: "
                << static_cast<int>(im->at<char>(cv::Point(x,y))) << std::endl;
                break;
  }
}

int main(){
  cv::Mat image;

  image = cv::imread("images/coin-1.JPG");

  if(image.empty()){
    std::cout<< "Image is empty" << std::endl;
  }

  cv::namedWindow("Original Image");
  cv::imshow("Original Image", image);
  cv::setMouseCallback("Original Image", onMouse, reinterpret_cast<void*>(&image));

  cv::waitKey(0);
  return 0;
}