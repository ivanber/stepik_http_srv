#include "app_cfg_reader.h"
#include <iostream>
#include "log.h"
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
#ifndef CONSOLE
  if (fork() == 0) {
#endif
    signal(SIGINT, intHandler);

    logger.reset( new std::ofstream("final.log") );

    AppCfg cfg;
    AppCfgReader::read(argc, argv, cfg);

    auto const srvCfg = cfg.tcpServerCfg();

    ( *logger.get() ) << "host = " << srvCfg.host()
      << ", port = " << srvCfg.port()
      << ", rootDir = " << cfg.rootDir() << std::endl;

    TCPConnection::documentRoot = cfg.rootDir();

    TCPServer srv(service, srvCfg);

    std::cout << "Run server" << std::endl;

    service.run();

    std::cout << "Server stopped" << std::endl;
#ifndef CONSOLE
  }
#endif
  return 0;
}
//------------------------------------------------------------------------------
