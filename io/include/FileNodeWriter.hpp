#ifndef __OBOTCHA_FILE_NODE_WRITER_HPP__
#define __OBOTCHA_FILE_NODE_WRITER_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(FileNodeWriter) {
  public:
    _FileNodeWriter(String path);

    int write(int);

    int write(long);

    int write(String);

    int write(ByteArray);

    String getPath();

    ~_FileNodeWriter();

  private:
    String mPath;

    int mFd;
};

} // namespace obotcha
#endif
