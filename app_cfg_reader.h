#ifndef APP_CFG_READER_H__
#define APP_CFG_READER_H__
//------------------------------------------------------------------------------
#include "app_cfg.h"
//------------------------------------------------------------------------------
class AppCfgReader {
public:
  static void read(int argc, char *argv[], AppCfg &aCfg);
};
//------------------------------------------------------------------------------
#endif // APP_CFG_READER_H__
