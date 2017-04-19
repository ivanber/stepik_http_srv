#include "http_response_generator.h"
#include "tcp_connection.h"
//------------------------------------------------------------------------------
std::string TCPConnection::documentRoot;
//------------------------------------------------------------------------------
TCPConnection::TCPConnection(boost::asio::io_service &aService)
  : fSocket( new boost::asio::ip::tcp::socket(aService) ),
    fBuffer(BUF_SIZE) {}
//------------------------------------------------------------------------------
TCPConnection::~TCPConnection() {
  std::cout << "Destroy connection" << std::endl;
}
//------------------------------------------------------------------------------
void TCPConnection::start() {
  auto self( shared_from_this() );
  fSocket->async_read_some(
    boost::asio::buffer(fBuffer),
    [this, self](boost::system::error_code const &aErr, size_t const &aBytes) {
      if (!aErr) {
        std::string document;
        if ( fRequestParser.parse(fBuffer.data(), aBytes, document) ) {
          std::cout << "Parsed document : " << document << std::endl;

          HTTPResponseGenerator::generate(documentRoot, document, fResponse);

          sendResponse();
        } else {
          start();
        }
      } else {
        std::cerr << "Fault recv : " << aErr.message() << std::endl;
      }
    }
  );
}
//------------------------------------------------------------------------------
void TCPConnection::sendResponse() {
  auto self( shared_from_this() );
  auto const responseStr = fResponse.str();
  fSocket->async_send(
    boost::asio::buffer(responseStr),
    [this, self](boost::system::error_code const &aErr, size_t const &aBytes)
    {
      if (!aErr) {
        std::cout << "Response sended" << std::endl;
      } else {
        std::cerr << "Fault send : " << aErr.message() << std::endl;
      }
    }
  );
}
//------------------------------------------------------------------------------

