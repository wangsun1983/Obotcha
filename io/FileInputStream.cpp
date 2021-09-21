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
#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "Log.hpp"
#include <iostream>

namespace obotcha {

_FileInputStream::_FileInputStream(File f)
    : _FileInputStream(f->getAbsolutePath()) {}

_FileInputStream::_FileInputStream(const char *path)
    : _FileInputStream(createString(path)) {}

_FileInputStream::_FileInputStream(String path) {
    mPath = createString(path);
    this->fd = -1;
}

_FileInputStream::_FileInputStream(int fd) {
    mPath = nullptr;
    this->fd = fd;
}

ByteArray _FileInputStream::read(int size) {
    ByteArray data = createByteArray(size);
    int length = ::read(fd, data->toValue(), data->size());
    if (length <= 0) {
        return nullptr;
    } else if (length < data->size()) {
        data->quickShrink(length);
    }
    return data;
}

int _FileInputStream::seekTo(int index) { return lseek(fd, index, SEEK_SET); }

long _FileInputStream::readTo(ByteArray buff, int pos, int length) {
    int len = (length == 0) ? buff->size() : length;
    return ::read(fd, buff->toValue() + pos, len);
}

long _FileInputStream::read(ByteArray data) {
    return ::read(fd, data->toValue(), data->size());
}

long _FileInputStream::read(ByteArray data, int start) {
    return ::read(fd, &data->toValue()[start], data->size() - start);
}

ByteArray _FileInputStream::readAll() {
    struct stat stbuf;
    if ((fstat(fd, &stbuf) != 0) || (!S_ISREG(stbuf.st_mode))) {
        return nullptr;
    }

    return this->read(stbuf.st_size);
}

bool _FileInputStream::open() {
    if (fd >= 0) {
        return false;
    }

    fd = ::open(mPath->toChars(), O_RDONLY);
    return (fd >= 0);
}

void _FileInputStream::close() {
    if (fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}

void _FileInputStream::reset() {
    if (fd >= 0) {
        lseek(fd, 0, SEEK_SET);
    }
}

_FileInputStream::~_FileInputStream() { close(); }

} // namespace obotcha