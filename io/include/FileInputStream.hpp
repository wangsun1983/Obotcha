#ifndef __OBOTCHA_FILE_INPUT_STREAM_HPP__
#define __OBOTCHA_FILE_INPUT_STREAM_HPP__

#include <fstream>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(FileInputStream) IMPLEMENTS(InputStream) {
public:

    _FileInputStream(File f);
    
    _FileInputStream(String path);

    _FileInputStream(const char *);

    _FileInputStream(int fd);

    long read(ByteArray buffer);

    long readByLength(ByteArray buffer,int pos,int length);

    long read(long index,ByteArray buffer);

    ByteArray readAll();

    bool open();

    void close();

    void reset();

    ~_FileInputStream();

private:
    String mPath;

    int fd;
};

}
#endif
