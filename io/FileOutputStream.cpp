/**
 * @file FileOutputStream.cpp
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
#include "IO.hpp"

namespace obotcha {

_FileOutputStream::_FileOutputStream(File file)
    : _FileOutputStream(file->getAbsolutePath()) {

}

_FileOutputStream::_FileOutputStream(const char *path)
    : _FileOutputStream(createString(path)) {
}

_FileOutputStream::_FileOutputStream(String path):mPath(path) {
}

_FileOutputStream::_FileOutputStream(FileDescriptor fd):mPath(nullptr),
                                                        mFd(fd) {
}

long _FileOutputStream::write(char c) {
    Inspect(mFd == nullptr,-1)
    return ::write(mFd->getFd(), &c, 1);
}

long _FileOutputStream::write(ByteArray buff) {
    return write(buff,0);
}

long _FileOutputStream::write(ByteArray buff, uint64_t start) {
    return write(buff,start,buff->size() - start);
}

long _FileOutputStream::write(ByteArray buff, uint64_t start, uint64_t len) {
    Inspect(mFd == nullptr ||start + len > buff->size(),-1)
    return ::write(mFd->getFd(), &buff->toValue()[start], len);
}

long _FileOutputStream::writeString(String s) {
    Inspect(mFd == nullptr,-1)
    return ::write(mFd->getFd(), s->toChars(), s->size());
}

bool _FileOutputStream::open() {
    return this->open(st(IO)::FileControlFlags::Trunc | O_CREAT | O_RDWR);
}

bool _FileOutputStream::open(int options) {
    Inspect(mFd != nullptr,true)
    int fd = ::open(mPath->toChars(), O_CREAT | O_RDWR| options,S_IRUSR | S_IWUSR);
    if(fd > 0) {
        mFd = createFileDescriptor(fd);
    }
    return (fd >= 0);
}

void _FileOutputStream::close() {
    if(mPath != nullptr && mFd != nullptr) {
        mFd->close();
        mFd = nullptr;
    }
}

void _FileOutputStream::flush() {
    fdatasync(mFd->close());
}

} // namespace obotcha
