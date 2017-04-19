#include <boost/bind.hpp>
#include <iostream>
#include "tcp_server.h"
//------------------------------------------------------------------------------
TCPServer::TCPServer(boost::asio::io_service &aService,
  TCPServerCfg const &aCfg)
  : fAcceptor(
      aService,
      boost::asio::ip::tcp::endpoint( aCfg.host(), aCfg.port() )
    )
{
  fAcceptor.set_option( boost::asio::ip::tcp::acceptor::reuse_address(true) );

  startAccept();
}
//------------------------------------------------------------------------------
TCPServer::~TCPServer() {}
//------------------------------------------------------------------------------
void TCPServer::startAccept() {
  auto newConnection = TCPConnection::create( fAcceptor.get_io_service() );

  fAcceptor.async_accept(
    *newConnection->socket().get(),
    [this, newConnection](boost::system::error_code const &aErr) {
      if (!aErr) {
        std::cout << "Accepted new connection" << std::endl;

        newConnection->start();

        startAccept();
      } else {
        std::cerr << "Fault accept : " << aErr.message() << std::endl;
      }
    }
  );
}
//------------------------------------------------------------------------------
