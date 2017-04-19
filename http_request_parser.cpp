#include "http_request_parser.h"
//------------------------------------------------------------------------------
bool HTTPRequestParser::parse(char const *aBuf, size_t const aSize,
  std::string &aDocument)
{
  bool success = false;

  fStream.write(aBuf, aSize);

  auto const requestStr = fStream.str();
  if ( std::string::npos != requestStr.find("\r\n\r\n") ) {
    std::string line;
    while ( std::getline(fStream, line) ) {
      if (line.compare("GET ") >= 0)  {
        success = true;

        std::istringstream lineStream(line);

        std::string skip;
        std::getline(lineStream, skip, ' ');

        std::getline(lineStream, aDocument, ' ');

        break;
      }
    }
  }

  return success;
}
//------------------------------------------------------------------------------