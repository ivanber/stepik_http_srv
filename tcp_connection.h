#ifndef TCP_CONNECTION_H__
#define TCP_CONNECTION_H__
//------------------------------------------------------------------------------
#include <boost/asio.hpp>
#include "http_request_parser.h"
#include <memory>
#include <string>
#include <vector>
//------------------------------------------------------------------------------
// typedef std::shared_ptr< boost::asio::io_service > ServiceSPtr;
//------------------------------------------------------------------------------
class TCPConnection : public std::enable_shared_from_this< TCPConnection > {
public:
  typedef std::shared_ptr< boost::asio::ip::tcp::socket > TCPSocketSPtr;
  typedef std::shared_ptr< TCPConnection > TCPConnectionSPtr;
public:
  enum {BUF_SIZE = 10240};
public:
  static TCPConnectionSPtr create(boost::asio::io_service &aService) {
    return TCPConnectionSPtr( new TCPConnection(aService) );
  }
public:
  static std::string documentRoot;
public:
  ~TCPConnection();

  void start();

  TCPSocketSPtr socket() const { return fSocket; }
private:
  explicit TCPConnection(boost::asio::io_service &aService);

  void sendResponse();
private:
  TCPSocketSPtr fSocket;
  std::vector< char > fBuffer;
  std::ostringstream fResponse;
  HTTPRequestParser fRequestParser;
};
//------------------------------------------------------------------------------
#endif // TCP_CONNECTION_H__
