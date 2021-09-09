/**
 * @file FileInputStream.cpp
 * @brief A file output stream is an output stream for writing data to File
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <unistd.h>
#include <fcntl.h>

#include "FileOutputStream.hpp"

namespace obotcha {

_FileOutputStream::_FileOutputStream(File file):_FileOutputStream(file->getAbsolutePath()) {
}

_FileOutputStream::_FileOutputStream(const char *path):_FileOutputStream(createString(path)) {
}

_FileOutputStream::_FileOutputStream(String path) {
    mPath = path;
    fd = -1;
}

_FileOutputStream::_FileOutputStream(int fd) {
    mPath = nullptr;
    this->fd = fd;
}

long _FileOutputStream::write(char c) {
    return ::write(fd,&c,1);
}

long _FileOutputStream::write(ByteArray buff) {
    return ::write(fd,buff->toValue(),buff->size());
}

long _FileOutputStream::write(ByteArray buff,int start) {
    return ::write(fd,&buff->toValue()[start],buff->size() - start);
}

long _FileOutputStream::writeString(String s) {
    return ::write(fd,s->toChars(),s->size());
}

bool _FileOutputStream::open() {
    if(fd >= 0) {
        return false;
    }

    fd = ::open(mPath->toChars(),O_CREAT|O_RDWR|O_TRUNC,S_IRUSR|S_IWUSR);
    return (fd >= 0);
}

bool _FileOutputStream::open(int opentype) {
    if(fd >= 0) {
        return false;
    }

    switch(opentype) {
        case FileOpenType::Append:
            fd = ::open(mPath->toChars(),O_CREAT|O_RDWR|O_APPEND,S_IRUSR|S_IWUSR);
        break;

        case FileOpenType::Trunc:
            fd = ::open(mPath->toChars(),O_CREAT|O_RDWR|O_TRUNC,S_IRUSR|S_IWUSR);
        break;
    }

    return (fd >= 0);
}
    
void _FileOutputStream::close() {
    if(fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}

void _FileOutputStream::flush() {
    fdatasync(fd);
}

_FileOutputStream::~_FileOutputStream() {
    //close();
}

}