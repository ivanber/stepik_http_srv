#include "http_request_parser.h"
#include "log.h"
//------------------------------------------------------------------------------
bool HTTPRequestParser::parse(char const *aBuf, size_t const aSize,
  std::string &aDocument)
{
  bool success = false;

  fStream.write(aBuf, aSize);

  auto const requestStr = fStream.str();
  if ( std::string::npos != requestStr.find("\r\n\r\n")
    || std::string::npos != requestStr.find("\n\n") )
  {
    std::string line;
    while ( std::getline(fStream, line) ) {
      if (line.compare("GET ") >= 0)  {
        success = true;

        std::istringstream lineStream(line);

        std::string skip;
        std::getline(lineStream, skip, ' ');

        std::string document;
        std::getline(lineStream, document, ' ');

        std::istringstream documentStream(document);
        std::getline(documentStream, aDocument, '?');

        *logger.get() << "Parsed document " << aDocument << std::endl;

        break;
      }
    }
  }

  return success;
}
//------------------------------------------------------------------------------
