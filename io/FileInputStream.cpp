#include <sys/stat.h>
#include <algorithm>

#include "FileInputStream.hpp"
#include "IOException.hpp"
#include "Inspect.hpp"
#include "Log.hpp"

namespace obotcha {

_FileInputStream::_FileInputStream(File f): _FileInputStream(f->getAbsolutePath()) {
}

_FileInputStream::_FileInputStream(const char *path): _FileInputStream(createString(path)) {
}

_FileInputStream::_FileInputStream(String path):mPath(path),
                                                mIsFdImport(false) {
}

_FileInputStream::_FileInputStream(FileDescriptor fd):mFd(fd),
                                                      mIsFdImport(true) {
}

ByteArray _FileInputStream::read(int size) const {
    ByteArray data = createByteArray(size);
    ssize_t length = ::read(mFd->getFd(), data->toValue(), data->size());
    Inspect(length <= 0,nullptr)
    data->quickShrink(length);
    return data;
}

long _FileInputStream::seekTo(uint64_t index) const {
    return lseek(mFd->getFd(), index, SEEK_SET);
}

long _FileInputStream::read(ByteArray buff, uint64_t pos, uint64_t length) {
    long len = std::min(buff->size() - pos,length);
    return ::read(mFd->getFd(), buff->toValue() + pos, len);
}

long _FileInputStream::read(ByteArray data) {
    return ::read(mFd->getFd(), data->toValue(), data->size());
}

long _FileInputStream::read(ByteArray data, uint64_t start) {
    Inspect(start >= data->size(),-1)
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
    Inspect(mFd != nullptr,true)
    int fd = ::open(mPath->toChars(), O_RDONLY);
    Panic(fd < 0,IOException,"fail to open file,err is %s",strerror(errno))
    mFd = createFileDescriptor(fd);
    return true;
}

void _FileInputStream::close() {
    if(!mIsFdImport && mFd != nullptr) {
        mFd->close();
        mFd = nullptr;
    }
}

void _FileInputStream::reset() {
    if(mFd != nullptr) {
        lseek(mFd->getFd(), 0, SEEK_SET);
    }
}

_FileInputStream::~_FileInputStream() {
    close();
}

} // namespace obotcha
