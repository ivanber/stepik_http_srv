#ifndef HTTP_RESPONSE_GENERATOR_H__
#define HTTP_RESPONSE_GENERATOR_H__
//------------------------------------------------------------------------------
#include <iostream>
#include <string>
//------------------------------------------------------------------------------
class HTTPResponseGenerator {
public:
  static void generate(std::string const &aDocumentRoot,
    std::string const &aDocument, std::ostream &aStream);
};
//------------------------------------------------------------------------------
#endif // HTTP_RESPONSE_GENERATOR_H__
