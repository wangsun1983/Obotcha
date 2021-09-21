#ifndef __OBOTCHA_FILE_NODE_READER_HPP__
#define __OBOTCHA_FILE_NODE_READER_HPP__

#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(FileNodeReader) {
  public:
    _FileNodeReader(String path, int buffsize = 128);

    int readInt();

    bool readBoolean();

    long readLong();

    String readString();

    String getPath();

    ~_FileNodeReader();

  private:
    int mSize;

    String mPath;

    int mFd;
};

} // namespace obotcha
#endif
