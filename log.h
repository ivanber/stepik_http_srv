#ifndef LOG_H__
#define LOG_H__
//------------------------------------------------------------------------------
#include <fstream>
#include <memory>
//------------------------------------------------------------------------------
extern std::unique_ptr< std::ofstream > logger;
//------------------------------------------------------------------------------
#endif // LOG_H__
