#include "document_reader.h"
#include <fstream>
//------------------------------------------------------------------------------
bool DocumentReader::read(std::string const &aDocument, std::ostream &aStream) {
  bool success = false;

  std::ifstream ifl(aDocument, std::ios_base::in | std::ios_base::binary);
  if (ifl) {
    ifl.seekg(0, std::ios_base::end);
    auto const seekPos = ifl.tellg();
    ifl.seekg(0, std::ios_base::beg);

    int const bufSize = seekPos - ifl.tellg();
    if (bufSize >= 0) {
      success = true;

      auto buf = new char[bufSize];
      ifl.read(buf, bufSize);

      aStream.write(buf, bufSize);

      delete buf;
    }
  }

  return success;
}
//------------------------------------------------------------------------------
