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

#include "ArrayIndexOutOfBoundsException.hpp"
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
    mIsFdImport = false;
}

_FileOutputStream::_FileOutputStream(FileDescriptor fd) {
    mPath = nullptr;
    mFd = fd;
    mIsFdImport = true;
}

long _FileOutputStream::write(char c) {
    int fd = mFd->getFd();
    Inspect(fd < 0,-1);
    return ::write(fd, &c, 1);
}

long _FileOutputStream::write(ByteArray buff) {
    int fd = mFd->getFd();
    Inspect(fd < 0,-1);
    return ::write(fd, buff->toValue(), buff->size());
}

long _FileOutputStream::write(ByteArray buff, int start) {
    int fd = mFd->getFd();
    Inspect(fd < 0,-1);
    return ::write(fd, &buff->toValue()[start], buff->size() - start);
}

long _FileOutputStream::write(ByteArray buff, int start, int len) {
    int fd = mFd->getFd();
    Inspect(fd < 0,-1);
    if (len > (buff->size() - start)) {
        Trigger(ArrayIndexOutOfBoundsException, "out ouf bound");
    }

    return ::write(fd, &buff->toValue()[start], len);
}

long _FileOutputStream::writeString(String s) {
    int fd = mFd->getFd();
    Inspect(fd < 0,-1);
    return ::write(fd, s->toChars(), s->size());
}

bool _FileOutputStream::open() {
    Inspect(mFd != nullptr,false);
    auto fd = ::open(mPath->toChars(), O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
    mFd = createFileDescriptor(fd);
    return (fd >= 0);
}

bool _FileOutputStream::open(int opentype) {
    Inspect(mFd != nullptr,false);
    int fd = -1;
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

    mFd = createFileDescriptor(fd);
    return (fd >= 0);
}

void _FileOutputStream::close() {
    mFd->close();
}

void _FileOutputStream::flush() {
    fdatasync(mFd->close());
}

_FileOutputStream::~_FileOutputStream() {

}

} // namespace obotcha
