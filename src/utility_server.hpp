#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <functional>

typedef websocketpp::server<websocketpp::config::asio> server;

class utility_server {
public:
  utility_server() {
    // Set logging settings
    m_endpoint.set_error_channels(websocketpp::log::elevel::all);
    m_endpoint.set_access_channels(websocketpp::log::alevel::all ^ websocketpp::log::alevel::frame_payload);

    // Initialize Asio
    m_endpoint.init_asio();

    m_endpoint.set_message_handler(std::bind(
      &utility_server::echo_handler, this,
      std::placeholders::_1, std::placeholders::_2
    ));
  }

  void echo_handler(websocketpp::connection_hdl hdl, server::message_ptr msg) {
    m_endpoint.send(hdl, msg->get_payload(), msg->get_opcode());
  }

  void run() {
    m_endpoint.listen(9002);

    m_endpoint.start_accept();

    m_endpoint.run();
  }

private:
  server m_endpoint;
};
