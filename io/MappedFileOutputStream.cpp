#include "MappedFileOutputStream.hpp"

namespace obotcha {

_MappedFileOutputStream::_MappedFileOutputStream(MappedFile f) {
    mFile = f;
    mIndex = 0;
}

long _MappedFileOutputStream::write(char c) {
    if(mIndex >= mFile->size()) {
        return -EOVERFLOW;
    }

    mFile->mapPtr[mIndex] = c;
    mIndex++;

    return 1;
}

//mmap can not enlarge the file size.
long _MappedFileOutputStream::write(ByteArray buff) {
    return write(buff,0);
}

long _MappedFileOutputStream::write(ByteArray buff,int start) {
    return write(buff,start,buff->size() - start);
}

long _MappedFileOutputStream::write(ByteArray buff,int start,int len) {
    if (len > (buff->size() - start)) {
        return -EOVERFLOW;
    }

    if((mIndex + len) >= mFile->size()) {
        return -EOVERFLOW;
    }

    memcpy(mFile->mapPtr+mIndex,buff->toValue() + start,len);
    return len;
}

long _MappedFileOutputStream::writeString(String s) {
    write(s->toByteArray());
}

bool _MappedFileOutputStream::open(int opentype) {
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
