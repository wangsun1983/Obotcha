#ifndef __FILE_INPUT_STREAM_HPP__
#define __FILE_INPUT_STREAM_HPP__

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

    int read();

    long read(ByteArray buffer);

    ByteArray readAll();

    void readAll(ByteArray);

    bool open();

    void close();

    String readLine();

private:
    String mPath;

    std::ifstream fstream;

    long filesize;
};

}
#endif
