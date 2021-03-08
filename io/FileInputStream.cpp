/**
 * @file FileInputStream.cpp
 * @brief FileInputStream obtains input bytes from a file in a file system.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <iostream>
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Log.hpp"

namespace obotcha {

_FileInputStream::_FileInputStream(File f):_FileInputStream(f->getAbsolutePath()) {
}

_FileInputStream::_FileInputStream(const char *path):_FileInputStream(createString(path)) {
}

_FileInputStream::_FileInputStream(String path) {
    mPath = createString(path);
    this->fd = -1;
}

_FileInputStream::_FileInputStream(int fd) {
    mPath = nullptr;
    this->fd = fd;
}

long _FileInputStream::read(ByteArray buff) {
    return ::read(fd,buff->toValue(),buff->size());
}

long _FileInputStream::readByLength(ByteArray buffer,int pos,int len) {
    return ::read(fd,buffer->toValue() + pos,len);
}

long _FileInputStream::read(long index,ByteArray buffer) {
    lseek(fd,index,SEEK_SET);
    return read(buffer);
}

ByteArray _FileInputStream::readAll() {
    struct stat stbuf;
    if ((fstat(fd, &stbuf) != 0) || (!S_ISREG(stbuf.st_mode))) {
	    return nullptr;
	}

    long filesize = stbuf.st_size;
    ByteArray content = createByteArray(filesize);

    ::read(fd,content->toValue(),filesize);
    return content;
}

bool _FileInputStream::open() {
    if(fd >= 0) {
        return false;
    }
    
    fd = ::open(mPath->toChars(),O_RDONLY);
    return (fd >= 0);
}

void _FileInputStream::close() {
    if(fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}

void _FileInputStream::reset() {
    if(fd >= 0) {
        lseek(fd,0,SEEK_SET);
    }
}

_FileInputStream::~_FileInputStream() {
    close();
}

}