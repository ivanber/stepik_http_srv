#include "app_cfg_reader.h"
#include <iostream>
#include "tcp_connection.h"
#include "tcp_server.h"
//------------------------------------------------------------------------------
boost::asio::io_service service;
//------------------------------------------------------------------------------
void intHandler(int const aSignal) {
  if (SIGINT == aSignal) {
    service.stop();
  }
}
//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
   if (fork() == 0) {
    signal(SIGINT, intHandler);

    AppCfg cfg;
    AppCfgReader::read(argc, argv, cfg);

    TCPConnection::documentRoot = cfg.rootDir();

    TCPServer srv( service, cfg.tcpServerCfg() );

    std::cout << "Run server" << std::endl;

    service.run();

    std::cout << "Server stopped" << std::endl;
   }

  return 0;
}
//------------------------------------------------------------------------------
