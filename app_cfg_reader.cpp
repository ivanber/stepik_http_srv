#include "app_cfg_reader.h"
#include <iostream>
#include <unistd.h>
//------------------------------------------------------------------------------
void AppCfgReader::read(int argc, char *argv[], AppCfg &aCfg) {
  int opt = 0;

  while ( -1 != ( opt = getopt(argc, argv, "h:p:d:") ) ) {
    auto srvCfg = aCfg.tcpServerCfg();

    switch (opt) {
    case 'h':
      srvCfg.setHost( boost::asio::ip::address::from_string(optarg) );
      break;
    case 'p':
      srvCfg.setPort( std::stol(optarg) );
      break;
    case 'd':
      aCfg.setRootDir(optarg);
      break;
    case '?':
      std::cerr << "Use " << argv[0] << " -h <host> -p <port> -d <root>"
        << std::endl;
      break;
    }

    aCfg.setTCPServerCfg(srvCfg);
  }
}
//------------------------------------------------------------------------------
