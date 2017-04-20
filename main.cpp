#include "app_cfg_reader.h"
#include <iostream>
#include "log.h"
#include "tcp_connection.h"
#include "tcp_server.h"
#include <thread>
//------------------------------------------------------------------------------
static boost::asio::io_service service;
//------------------------------------------------------------------------------
void intHandler(int const aSignal) {
  if (SIGINT == aSignal) {
    service.stop();
  }
}
//------------------------------------------------------------------------------
void doWorker(boost::asio::io_service &aService) {
  std::cout << "Run io_service" << std::endl;
  aService.run();
  std::cout << "Stop io_service" << std::endl;
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

    std::thread worker( doWorker, std::ref(service) );

    std::cout << "Run server" << std::endl;
    worker.join();
    std::cout << "Server stopped" << std::endl;
#ifndef CONSOLE
  }
#endif
  return 0;
}
//------------------------------------------------------------------------------
