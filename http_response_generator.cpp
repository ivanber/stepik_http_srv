#include "document_mime_type_getter.h"
#include "document_reader.h"
#include "http_response_generator.h"
#include <sstream>
//------------------------------------------------------------------------------
void HTTPResponseGenerator::generate(std::string const &aDocumentRoot,
  std::string const &aDocument, std::ostream &aStream)
{
  aStream << "HTTP/1.0 ";

  std::string mimeType;
  std::stringstream documentStream;

  auto const documentName = aDocumentRoot + aDocument;
  if ( DocumentReader::read(documentName, documentStream) ) {
    aStream << "200 OK\r\n";

    mimeType = DocumentMimeTypeGetter::get(aDocument);
  } else {
    aStream << "404 Not Found\r\n";

    mimeType = "text/plain";

    documentStream << "Document " << aDocument << " is not found." << std::endl;
  }

  auto const contentLength = documentStream.tellp() - documentStream.tellg();
  aStream << "Server: stepik_final/0.0.9\r\n"
    << "Content-Length: " << contentLength << "\r\n"
    << "Content-Type: " << mimeType << "\r\n"
    << "Connection: Closed\r\n\r\n"
    << documentStream.str();
}
//------------------------------------------------------------------------------
