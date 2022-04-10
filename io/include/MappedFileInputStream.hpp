#ifndef __OBOTCHA_MAPPED_FILE_INPUT_STREAM_HPP__
#define __OBOTCHA_MAPPED_FILE_INPUT_STREAM_HPP__

#include <fstream>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "ByteArray.hpp"
#include "MappedFile.hpp"

namespace obotcha {

DECLARE_CLASS(MappedFileInputStream) IMPLEMENTS(InputStream) {
public:
    _MappedFileInputStream(MappedFile);

    long read(ByteArray);

    long read(ByteArray, int start);

    long read(ByteArray, int start,int length);
    
    ByteArray readAll();

    bool open();

    void close();

    ~_MappedFileInputStream();

private:
    MappedFile mFile;
    long mIndex;
};

}
#endif
