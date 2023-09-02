#include <algorithm>

#include "MappedFileInputStream.hpp"
#include "Inspect.hpp"

namespace obotcha {

_MappedFileInputStream::_MappedFileInputStream(MappedFile file):mFile(file) {
}

long _MappedFileInputStream::read(ByteArray data) {
    return this->read(data,0);
}

long _MappedFileInputStream::read(ByteArray data, uint64_t start) {
    return this->read(data,start,data->size());
}

long _MappedFileInputStream::read(ByteArray buff, uint64_t pos,uint64_t length) {
    Inspect(pos + length > buff->size(),-1)
    long len = std::min(mFile->size(),length);
    memcpy(buff->toValue() + pos,mFile->mapPtr,len);
    return len;
}

ByteArray _MappedFileInputStream::readAll() {
    return createByteArray(mFile->mapPtr,mFile->size());
}

bool _MappedFileInputStream::open() {
    return true;
}

void _MappedFileInputStream::close() {
    mFile = nullptr;
}

_MappedFileInputStream::~_MappedFileInputStream() {
    close();
}


}
