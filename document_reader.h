#ifndef DOCUMENT_READER_H__
#define DOCUMENT_READER_H__
//------------------------------------------------------------------------------
#include <iostream>
//------------------------------------------------------------------------------
class DocumentReader {
public:
  static bool read(std::string const &aDocument, std::ostream &aStream);
};
//------------------------------------------------------------------------------
#endif // DOCUMENT_READER_H__
