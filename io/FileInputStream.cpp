#include <iostream>

#include "FileInputStream.hpp"
#include "FileNotFoundException.hpp"
#include "IOException.hpp"
#include "Inspect.hpp"
#include "Log.hpp"


namespace obotcha {

_FileInputStream::_FileInputStream(File f)
    : _FileInputStream(f->getAbsolutePath()) {}

_FileInputStream::_FileInputStream(const char *path)
    : _FileInputStream(createString(path)) {}

_FileInputStream::_FileInputStream(String path) {
    mPath = createString(path);
    //this->fd = -1;
    mFd = nullptr;
    mIsFdImport = false;
}

_FileInputStream::_FileInputStream(FileDescriptor fd) {
    mPath = nullptr;
    mFd = fd;
    mIsFdImport = true;
}

ByteArray _FileInputStream::read(int size) {
    ByteArray data = createByteArray(size);
    int length = ::read(mFd->getFd(), data->toValue(), data->size());
    if (length <= 0) {
        return nullptr;
    } else if (length < data->size()) {
        data->quickShrink(length);
    }

    return data;
}

long _FileInputStream::seekTo(int index) { 
    return lseek(mFd->getFd(), index, SEEK_SET); 
}

long _FileInputStream::read(ByteArray buff, int pos, int length) {
    long len = ((pos + length) > buff->size()) ? buff->size() : length;
    return ::read(mFd->getFd(), buff->toValue() + pos, len);;
}

long _FileInputStream::read(ByteArray data) {
    return ::read(mFd->getFd(), data->toValue(), data->size());
}

long _FileInputStream::read(ByteArray data, int start) {
    return ::read(mFd->getFd(), &data->toValue()[start], data->size() - start);
}

ByteArray _FileInputStream::readAll() {
    struct stat stbuf = {0};
    if ((fstat(mFd->getFd(), &stbuf) != 0) || (!S_ISREG(stbuf.st_mode))) {
        return nullptr;
    }

    return this->read(stbuf.st_size);
}

bool _FileInputStream::open() {
    Inspect(mFd != nullptr,true);

    int fd = ::open(mPath->toChars(), O_RDONLY);
    if(fd < 0) {
        Trigger(IOException,"fail to open file,err is %s",strerror(errno));
    }

    mFd = createFileDescriptor(fd);
    return true;
}

void _FileInputStream::close() {
    if(!mIsFdImport) {
        mFd->close();
    }
}

void _FileInputStream::reset() {
    int fd = mFd->getFd();
    if(fd >= 0) {
        lseek(fd, 0, SEEK_SET);
    }
}

_FileInputStream::~_FileInputStream() { 
    close();
}

} // namespace obotcha