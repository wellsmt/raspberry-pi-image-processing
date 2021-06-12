#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <iostream>
#include <functional>
#include "utility_server.hpp"

int main(int argc, char* argv[]) {
  utility_server s;
  s.run();
  return 0;
}
