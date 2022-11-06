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

#include <fcntl.h>
#include <unistd.h>

#include "ArrayIndexOutOfBoundsException.hpp"
#include "Exception.hpp"
#include "FileOutputStream.hpp"
#include "Inspect.hpp"

namespace obotcha {

_FileOutputStream::_FileOutputStream(File file)
    : _FileOutputStream(file->getAbsolutePath()) {

}

_FileOutputStream::_FileOutputStream(const char *path)
    : _FileOutputStream(createString(path)) {

}

_FileOutputStream::_FileOutputStream(String path) {
    mPath = path;
    fd = -1;
    isFdImport = false;
}

_FileOutputStream::_FileOutputStream(int fd) {
    mPath = nullptr;
    this->fd = fd;
    isFdImport = true;
}

long _FileOutputStream::write(char c) {
    // if (fd < 0) {
    //     return -1;
    // }
    Inspect(fd < 0,-1);

    return ::write(fd, &c, 1);
}

long _FileOutputStream::write(ByteArray buff) {
    // if (fd < 0) {
    //     return -1;
    // }
    Inspect(fd < 0,-1);

    return ::write(fd, buff->toValue(), buff->size());
}

long _FileOutputStream::write(ByteArray buff, int start) {
    // if (fd < 0) {
    //     return -1;
    // }
    Inspect(fd < 0,-1);

    return ::write(fd, &buff->toValue()[start], buff->size() - start);
}

long _FileOutputStream::write(ByteArray buff, int start, int len) {
    // if (fd < 0) {
    //     return -1;
    // }
    Inspect(fd < 0,-1);

    if (len > (buff->size() - start)) {
        Trigger(ArrayIndexOutOfBoundsException, "out ouf bound");
    }

    return ::write(fd, &buff->toValue()[start], len);
}

long _FileOutputStream::writeString(String s) {
    // if (fd < 0) {
    //     return -1;
    // }
    Inspect(fd < 0,-1);

    return ::write(fd, s->toChars(), s->size());
}

bool _FileOutputStream::open() {
    // if (fd >= 0) {
    //     return false;
    // }
    Inspect(fd >= 0,false);

    fd = ::open(mPath->toChars(), O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    return (fd >= 0);
}

bool _FileOutputStream::open(int opentype) {
    // if (fd >= 0) {
    //     return false;
    // }
    Inspect(fd >= 0,false);

    switch (opentype) {
    case FileOpenType::Append:
        fd = ::open(mPath->toChars(), O_CREAT | O_RDWR | O_APPEND,
                    S_IRUSR | S_IWUSR);
        break;

    case FileOpenType::Trunc:
        fd = ::open(mPath->toChars(), O_CREAT | O_RDWR | O_TRUNC,
                    S_IRUSR | S_IWUSR);
        break;
    }

    return (fd >= 0);
}

void _FileOutputStream::close() {
    if (fd >= 0) {
        ::close(fd);
        fd = -1;
    }
}

void _FileOutputStream::flush() {
    fdatasync(fd);
}

_FileOutputStream::~_FileOutputStream() {
    if(!isFdImport) {
       close();
    }
}

} // namespace obotcha
