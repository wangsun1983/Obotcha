#include <stdlib.h>
#include <memory.h>

#include "ByteArray.hpp"

namespace obotcha {

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
}

byte *_ByteArray::toValue() {
    return buff;
}

int _ByteArray::size() {
    return _size;
}

}