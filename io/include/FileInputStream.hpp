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

DECLARE_CLASS(FileInputStream) IMPLEMENTS(InputStream) {
public:

    _FileInputStream(File f);
    
    _FileInputStream(String path);

    _FileInputStream(const char *);

    _FileInputStream(int fd);

    ByteArray read(int size = 1024*4);

    long read(ByteArray);
    long read(ByteArray,int start);

    int seekTo(int index);
    
    long readTo(ByteArray,int pos = 0,int length = 0);

    ByteArray readAll();

    bool open();

    void close();

    void reset();

    ~_FileInputStream();

private:
    String mPath;

    int fd;

    bool isFdImport;
};

}
#endif
