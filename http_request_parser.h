#ifndef HTTP_REQUEST_PARSER_H__
#define HTTP_REQUEST_PARSER_H__
//------------------------------------------------------------------------------
#include <sstream>
#include <string>
//------------------------------------------------------------------------------
class HTTPRequestParser {
public:
  bool parse(char const *aBuf, size_t const aSize, std::string &aDocument);
private:
  std::stringstream fStream;
};
//------------------------------------------------------------------------------
#endif // HTTP_REQUEST_PARSER_H__
