#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>

int main(){
  cv::VideoCapture cap(0);

  if(!cap.isOpened())
    return -1;

  cv::Mat edges;
  size_t frame_index = 0;
  std::stringstream frame_name;
  for(;;)
  {
    // Only keep 20 frames saved to disk for testing 
    if(frame_index == 20) frame_index = 0; 
    frame_name.str(std::string());

    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
    cv::Canny(edges, edges, 0, 30, 3);
    frame_index++;
    frame_name << "FRAME_" << frame_index << ".JPG";
    cv::imwrite(frame_name.str(), edges);
  }
  return 0;
}
