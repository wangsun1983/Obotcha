#ifndef __OBOTCHA_MEMORY_FILE_INPUT_STREAM_HPP__
#define __OBOTCHA_MEMORY_FILE_INPUT_STREAM_HPP__

#include <fstream>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "MemoryFile.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(MemoryFileInputStream) IMPLEMENTS(InputStream) {
public:

    _MemoryFileInputStream(MemoryFile f);
    
    _MemoryFileInputStream(String path);

    int read();

    long read(ByteArray buffer);

    long read(int index,ByteArray buffer);

    ByteArray readAll();

    bool open();

    void close();

    ~_MemoryFileInputStream();
private:
    String mPath;

    long filesize;

    unsigned char *mPtr;
};

}
#endif
