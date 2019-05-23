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

_ByteArray::_ByteArray(String str) {
    int size = str->size();
    _size = size + 1;
    buff = (char *)malloc(_size);
    memset(buff,0,_size);

    memcpy(buff,str->toChars(),size);
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

bool _ByteArray::resize(int size) {
    if(size <= _size) {
        return false;
    }

    char *toFree = buff;

    buff = (char *)malloc(size);
    memset(buff,0,size);
    memcpy(buff,toFree,_size);
    _size = size;

    if(toFree != nullptr) {
        free(toFree);
    }

    return true;
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

bool _ByteArray::fill(byte v) {
    if(buff == nullptr) {
        return false;
    }

    memset(buff,v,_size);
    
    return true;
}

bool _ByteArray::fill(int index,byte v) {
    if(buff == nullptr) {
        return false;
    }

    if(index >= _size || index < 0) {
        return false;
    }

    buff[index] = v;

    return true;
}

bool _ByteArray::fill(int index,int length,byte v) {
    if(buff == nullptr) {
        return false;
    }

    if((index >= _size) 
        || (index < 0)
        || (index + length > _size)) {
        return false;
    }

    memset(&buff[index],v,length);

    return true;
}

}
