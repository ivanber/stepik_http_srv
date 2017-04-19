#ifndef TCP_SERVER_H__
#define TCP_SERVER_H__
//------------------------------------------------------------------------------
#include <cstdint>
#include <boost/asio.hpp>
#include <string>
#include "tcp_connection.h"
//------------------------------------------------------------------------------
class TCPServerCfg {
public:
  TCPServerCfg() : fHost( boost::asio::ip::address::from_string("127.0.0.1") ),
    fPort(80) {}

  boost::asio::ip::address host() const { return fHost; }
  void setHost(boost::asio::ip::address const &aVal) { fHost = aVal; }

  uint16_t port() const { return fPort; }
  void setPort(uint16_t const aVal) { fPort = aVal; }
private:
  boost::asio::ip::address fHost;
  uint16_t fPort;
};
//------------------------------------------------------------------------------
class TCPServer {
public:
  TCPServer(boost::asio::io_service &aService, TCPServerCfg const &aCfg);
  ~TCPServer();
private:
  void startAccept();
private:
  boost::asio::ip::tcp::acceptor fAcceptor;
};
//------------------------------------------------------------------------------
#endif // TCP_SERVER_H__
