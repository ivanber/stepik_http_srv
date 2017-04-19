#ifndef DOCUMENT_MIME_TYPE_GETTER_H__
#define DOCUMENT_MIME_TYPE_GETTER_H__
//------------------------------------------------------------------------------
#include <string>
//------------------------------------------------------------------------------
class DocumentMimeTypeGetter {
public:
  static std::string get(std::string const &aDocument);
};
//------------------------------------------------------------------------------
#endif // DOCUMENT_MIME_TYPE_GETTER_H__
