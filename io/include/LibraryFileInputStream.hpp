#ifndef __OBOTCHA_LIBRARY_INPUT_STREAM_HPP__
#define __OBOTCHA_LIBRARY_INPUT_STREAM_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "LibraryFile.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(LibraryFileInputStream) IMPLEMENTS(InputStream) {
  public:
    _LibraryFileInputStream(LibraryFile f);

    _LibraryFileInputStream(String path);

    int read();

    long read(ByteArray);

    bool open();

    void close();

    void *getMethod(String);

  private:
    void *mHandle;

    LibraryFile mFile;
};

} // namespace obotcha
#endif
