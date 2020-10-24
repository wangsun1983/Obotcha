/**
 * @file FileNodeReader.cpp
 * @brief write data to file data(like dev/xxxx)
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_198£³£Àyahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <fcntl.h>

#include "String.hpp"
#include "FileNodeWriter.hpp"
#include "FileNotFoundException.hpp"

namespace obotcha {

_FileNodeWriter::_FileNodeWriter(String path) {
    mPath = path;
    mFd = open(path->toChars(),O_WRONLY);
    if(mFd < 0) {
        throw FileNotFoundException("File not exist");
    }
}

int _FileNodeWriter::write(int v) {
    String value = createString(v);
    return ::write(mFd,value->toChars(),value->size());
}

int _FileNodeWriter::write(long v) {
    String value = createString(v);
    return ::write(mFd,value->toChars(),value->size());
}

int _FileNodeWriter::write(String v) {
    return ::write(mFd,v->toChars(),v->size());
}

int _FileNodeWriter::write(ByteArray value) {
    return ::write(mFd,value->toValue(),value->size());
}

String _FileNodeWriter::getPath() {
    return mPath;
}

_FileNodeWriter::~_FileNodeWriter() {
    if(mFd >= 0) {
        close(mFd);
        mFd = -1;
    }
}

}

