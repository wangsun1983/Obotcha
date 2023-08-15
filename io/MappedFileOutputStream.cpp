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

long _MappedFileOutputStream::write(ByteArray buff,int start) {
    return write(buff,start,buff->size() - start);
}

long _MappedFileOutputStream::write(ByteArray buff,int start,int len) {
    Inspect((start + len) > buff->size(),-EOVERFLOW)
    memcpy(mFile->mapPtr,buff->toValue() + start,len);
    return len;
}

long _MappedFileOutputStream::writeString(String s) {
    return write(s->toByteArray());
}

bool _MappedFileOutputStream::open(st(IO)::FileControlFlags) {
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
