#ifndef __OBOTCHA_FILE_NODE_WRITER_HPP__
#define __OBOTCHA_FILE_NODE_WRITER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FileNodeWriter) {
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

}
#endif
