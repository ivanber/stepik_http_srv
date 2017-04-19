#include "document_reader.h"
#include <fstream>
#include "log.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//------------------------------------------------------------------------------
int isRegularFile(const char *aPath)
{
  struct stat path_stat;
  stat(aPath, &path_stat);
  return S_ISREG(path_stat.st_mode);
}
//------------------------------------------------------------------------------
bool DocumentReader::read(std::string const &aDocument, std::ostream &aStream) {
  bool success = false;

  if ( isRegularFile( aDocument.c_str() ) ) {
    *logger.get() << aDocument << " is regular file" << std::endl;

    std::ifstream ifl(aDocument, std::ios_base::in | std::ios_base::binary);
    if (ifl) {
      ifl.seekg(0, std::ios_base::end);
      auto const seekPos = ifl.tellg();
      ifl.seekg(0, std::ios_base::beg);

      int const bufSize = seekPos - ifl.tellg();
      if (bufSize >= 0) {
        *logger.get() << aDocument << " size = " << bufSize << std::endl;

        success = true;

        auto buf = new char[bufSize];
        ifl.read(buf, bufSize);

        aStream.write(buf, bufSize);

        delete buf;
      }
    }
  }

  return success;
}
//------------------------------------------------------------------------------
