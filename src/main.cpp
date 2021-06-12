#include <boost/interprocess/managed_shared_memory.hpp>
#include <chrono>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <functional>
#include <mutex>
#include <set>
#include <thread>
#include <vector>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

class broadcast_server {
public:
  broadcast_server() {
    m_server.init_asio();

    m_server.set_open_handler(bind(&broadcast_server::on_open, this, ::_1));
    m_server.set_close_handler(bind(&broadcast_server::on_close, this, ::_1));
    m_server.set_message_handler(bind(&broadcast_server::on_message, this, ::_1, ::_2));
  }

  void on_open(connection_hdl hdl) {
    m_connections.insert(hdl);
  }

  void on_close(connection_hdl hdl) {
    m_connections.erase(hdl);
  }

  void on_message(connection_hdl hdl, server::message_ptr msg) {
    for (auto it : m_connections) {
      m_server.send(it, msg);
    }
  }

  void count() {
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
      return;
    cv::Mat gray;
    m_count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff;
    float fps = 0;
    while (true) {
      if (m_count == 20)
      {
        auto end = std::chrono::high_resolution_clock::now(); 
        std::chrono::duration<double> diff = end-start;
        fps = 20.0/diff.count();
        start = std::chrono::high_resolution_clock::now(); 
        m_count = 0;
      }
      //TODO: Make an image
      cv::Mat frame;
      cap >> frame; // get a new frame from camera

      cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

      //TODO: Write image to stringstream
      std::stringstream ss;
      std::vector<unsigned char> buf;
      int params[3] = {0};
      params[0] = 1;
      params[1] = 100;
      bool code = cv::imencode(".jpg", frame, buf,  std::vector<int>(params, params+2));
      unsigned char* grayPtr = reinterpret_cast<unsigned char*> (&buf[0]);

      std::string base64string = websocketpp::base64_encode(grayPtr, buf.size());
      /*
      std::ofstream myfile;
      myfile.open ("base64string.txt");
      myfile << base64string;
      myfile.close();
      */
      ss << fps << " " << gray.cols << " " << gray.rows << " " << base64string;
      //cv::imwrite("IMAGE.JPG", gray);
      

      //TODO: Send image over websocket
      std::lock_guard<std::mutex> lock(m_mutex);
      for (auto it : m_connections) {
        m_server.send(it, ss.str(), websocketpp::frame::opcode::text);
        m_count++;
      }
    }
  }

  void run(uint16_t port) {
    m_server.listen(port);
    m_server.start_accept();
    m_server.run();
  }
private:
  typedef std::set<connection_hdl, std::owner_less<connection_hdl>> con_list;

  int m_count;
  std::mutex m_mutex;
  server m_server;
  con_list m_connections;
};

int main() {
  broadcast_server s;
  std::thread t(std::bind(&broadcast_server::count, &s));
  s.run(9002);
/*
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
  */
  return 0;
}
