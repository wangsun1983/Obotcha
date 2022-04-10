#include "MappedFileInputStream.hpp"

namespace obotcha {

_MappedFileInputStream::_MappedFileInputStream(MappedFile file) {
    mFile = file;
    mIndex = 0;
}

long _MappedFileInputStream::read(ByteArray data) {
    return this->read(data,0);
}

long _MappedFileInputStream::read(ByteArray data, int start) {
    return this->read(data,start,data->size());
}

long _MappedFileInputStream::read(ByteArray buff, int pos,int length) {
    printf("pos is %d,length is %d,buff size is %d \n",pos,length,buff->size());
    long len = ((pos + length) > buff->size()) ? buff->size() : (long)length;
    if(len > mFile->size() - mIndex - 1) {
        len = mFile->size() - mIndex;
    }
    printf("len is %d,mapPtr is %lx \n",len,mFile->mapPtr);
    memcpy(buff->toValue() + pos,mFile->mapPtr + mIndex,len);
    mIndex += len;
    return len;
}

ByteArray _MappedFileInputStream::readAll() {
    return createByteArray((const byte *)mFile->mapPtr,mFile->size());
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
