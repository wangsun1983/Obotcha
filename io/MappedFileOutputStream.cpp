/**
 * @file MappedFileOutputStream.cpp
 * @brief MappedFileOutputStream is meant for write memory-mapped file of raw bytes 
 *        such as image data.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
#include "MappedFileOutputStream.hpp"
#include "Inspect.hpp"

namespace obotcha {

_MappedFileOutputStream::_MappedFileOutputStream(MappedFile f):mFile(f) {
}

long _MappedFileOutputStream::write(char c) {
    Inspect(mFile->mSize <= 0,-1)
    mFile->mapPtr[0] = c;
    return 1;
}

//mmap can not enlarge the file size.
long _MappedFileOutputStream::write(ByteArray buff) {
    return write(buff,0);
}

long _MappedFileOutputStream::write(ByteArray buff,uint64_t start) {
    return write(buff,start,buff->size() - start);
}

long _MappedFileOutputStream::write(ByteArray buff,uint64_t start,uint64_t len) {
    Inspect((start + len) > buff->size(),-EOVERFLOW)
    memcpy(mFile->mapPtr,buff->toValue() + start,len);
    return len;
}

long _MappedFileOutputStream::writeString(String s) {
    return write(s->toByteArray());
}

bool _MappedFileOutputStream::open(int options) {
    return true;
}

bool _MappedFileOutputStream::open() {
    return true;
}

void _MappedFileOutputStream::close() {
    this->mFile = nullptr;
}

void _MappedFileOutputStream::flush() {
    msync((void *)mFile->mapPtr, mFile->size(), MS_SYNC);
}

_MappedFileOutputStream::~_MappedFileOutputStream() {
    close();
}


}
