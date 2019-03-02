#include <boost/interprocess/managed_shared_memory.hpp>
#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>

int main() {
  boost::interprocess::managed_shared_memory segment(
      boost::interprocess::open_or_create, "MySharedMemory", 1400000);
  std::cout << "Capture Video" << std::endl;
  cv::VideoCapture cap(0);

  if (!cap.isOpened())
    return -1;

  cv::Mat edges;
  size_t frame_index = 0;
  std::stringstream frame_name;
  auto start = std::chrono::high_resolution_clock::now(); 
  for (;;) {
    if (frame_index == 20)
    {
      auto end = std::chrono::high_resolution_clock::now(); 
      std::chrono::duration<double> diff = end-start;
      std::cout << "Time to Blur and Canny on 20 images " 
                  << " : " << 20.0/diff.count() << "fps\n";  
      start = std::chrono::high_resolution_clock::now(); 
      frame_index = 0;
    } 
    frame_name.str(std::string());

    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
    cv::Canny(edges, edges, 0, 30, 3);

    frame_index++;
    frame_name << "FRAME_" << frame_index << ".JPG";
    cv::Mat *p = segment.construct<cv::Mat>(frame_name.str().c_str())(edges);
    auto f = segment.find<cv::Mat>(frame_name.str().c_str());
    if(f.first)
    {
      cv::imwrite(frame_name.str(), *f.first);
    }
    bool destroyed = segment.destroy<cv::Mat>(frame_name.str().c_str());
    if (!destroyed) {
      std::cout << "FAILED to DESTROY " << frame_name.str() << std::endl;
    }
    boost::interprocess::shared_memory_object::remove("MySharedMemory");
  }
  return 0;
}
