#include <stdlib.h>
#include <memory.h>

#include "ByteArray.hpp"

namespace obotcha {

_ByteArray::_ByteArray(sp<_ByteArray> b) {
    buff = (char *)malloc(b->size());
    memcpy(buff,b->toValue(),b->size());
}

_ByteArray::_ByteArray(int length) {
    buff = (char *)malloc(length);
    memset(buff,0,length);
    _size = length;
}

_ByteArray::_ByteArray(byte *data,int len) {
    buff = (char *)malloc(len);
    memset(buff,0,len);
    _size = len;
    memcpy(buff,data,len);
}

void _ByteArray::clear() {
    memset(buff,0,_size);
}

_ByteArray::~_ByteArray() {
    if(buff != nullptr) {
        free(buff);
    }
    _size = 0;
}

byte *_ByteArray::toValue() {
    return buff;
}

int _ByteArray::size() {
    return _size;
}

void _ByteArray::resize(int size) {
    if(buff != nullptr) {
        free(buff);
    }

    buff = (char *)malloc(size);
    memset(buff,0,size);
    _size = size;
}

bool _ByteArray::isEmpty() {
    if(buff == nullptr || _size == 0) {
        return true;
    }

    return false;
}

byte _ByteArray::at(int index) {
    return buff[index];
}

void _ByteArray::fill(byte v) {
    if(buff == nullptr) {
        return;
    }

    memset(buff,v,_size);
}

}
