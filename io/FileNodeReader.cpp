/**
 * @file FileNodeReader.cpp
 * @brief Read data from file node(like dev/xxxxx)
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <fcntl.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/types.h>
#include <unistd.h>

#include "ArrayList.hpp"
#include "FileInputStream.hpp"
#include "FileNodeReader.hpp"
#include "String.hpp"

namespace obotcha {

_FileNodeReader::_FileNodeReader(String path, int buffsize) {
    mSize = buffsize;
    mPath = path;
    mFd = open(mPath->toChars(), O_RDONLY);
}

int _FileNodeReader::readInt() {
    byte buff[mSize];
    memset(buff, 0, mSize);

    read(mFd, buff, mSize);
    return std::atoi((const char *)buff);
}

long _FileNodeReader::readLong() {
    byte buff[mSize];
    memset(buff, 0, mSize);

    read(mFd, buff, mSize);
    return std::atol((const char *)buff);
}

bool _FileNodeReader::readBoolean() {
    byte buff[mSize];
    memset(buff, 0, mSize);

    read(mFd, buff, mSize);
    return createString((const char *)buff)->toBasicBool();
}

String _FileNodeReader::readString() {
    byte buff[mSize];
    memset(buff, 0, mSize);

    read(mFd, buff, mSize);
    ;
    return createString((const char *)buff);
}

String _FileNodeReader::getPath() { return mPath; }

_FileNodeReader::~_FileNodeReader() {
    if (mFd >= 0) {
        close(mFd);
        mFd = -1;
    }
}

} // namespace obotcha
