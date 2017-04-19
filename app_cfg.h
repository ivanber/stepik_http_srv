#ifndef APP_CFG_H__
#define APP_CFG_H__
//------------------------------------------------------------------------------
#include "tcp_server.h"
//------------------------------------------------------------------------------
class AppCfg {
public:
  AppCfg() : fRootDir(".") {}

  TCPServerCfg tcpServerCfg() const { return fTCPServerCfg; }
  void setTCPServerCfg(TCPServerCfg const &aVal) { fTCPServerCfg = aVal; }

  std::string rootDir() const { return fRootDir; }
  void setRootDir(std::string const &aVal) { fRootDir = aVal; }
private:
  TCPServerCfg fTCPServerCfg;
  std::string fRootDir;
};
//------------------------------------------------------------------------------
#endif // APP_CFG_H__
