/**
 * @file ByteArray.cpp
 * @brief this class used for memory operation as buffer
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Error.hpp"
#include "ByteArray.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

const int _ByteArray::SafeMode = 1;

const int _ByteArray::NormalMode = 2;

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(sp<_ByteArray> b) {
    mSize = b->size();
    buff = (unsigned char *)malloc(mSize);
    memcpy(buff,b->toValue(),mSize);
    mMode = NormalMode;
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(int length) {
    buff = (unsigned char *)malloc(length);
    memset(buff,0,length);
    mSize = length;
    mMode = NormalMode;
}

/**
 * @brief ByteArray construct function
 * @param str save str as ByteArray
 */
_ByteArray::_ByteArray(String str) {
    mSize = str->size();
    buff = (unsigned char *)malloc(mSize + 1);
    memset(buff,0,mSize + 1);
    memcpy(buff,str->toChars(),mSize);
    mMode = NormalMode;
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(const byte *data,uint32_t len) {
    buff = (unsigned char *)malloc(len);
    mSize = len;
    memcpy(buff,data,len);
    mMode = NormalMode;
}

void _ByteArray::setMode(int mode) {
    mMode = mode;
}

/**
 * @brief clear memory data
 */
void _ByteArray::clear() {
    memset(buff,0,mSize);
}

unsigned char & _ByteArray::operator[] (int i) { 
        return buff[i];
}

/**
 * @brief ByteArray destruct function
 */
_ByteArray::~_ByteArray() {
    if(buff != nullptr) {
        free(buff);
        buff = nullptr;
    }

    mSize = 0;
}


byte *_ByteArray::toValue() {
    if(mMode == SafeMode) {
        byte *v = (byte*)malloc(mSize);
        memcpy(v,buff,mSize);
        return v;
    }
    
    return buff;
}

int _ByteArray::size() {
    return mSize;
}

void _ByteArray::qucikShrink(int size) {
    if(size >= mSize) {
        return;
    }

    buff[size] = 0;
    mSize = size;
}

int _ByteArray::resize(int size) {
    if(size <= mSize) {
        return -InvalidParam;
    }

    if(buff == nullptr) {
        return -NotCreate;
    }

    buff = (byte *)realloc(buff,size);

    mSize = size;    
    
    return 0;
}

bool _ByteArray::isEmpty() {
    return (buff == nullptr || mSize == 0);
}

byte _ByteArray::at(int index) {
    if(index >= mSize) {
        throw ArrayIndexOutOfBoundsException("ByteArray",mSize,index);
    }
    return buff[index];
}

int _ByteArray::fill(byte v) {
    if(buff == nullptr) {
        return -NotCreate;
    }

    memset(buff,v,mSize);
    
    return 0;
}

int _ByteArray::fill(int index,byte v) {
    if(buff == nullptr) {
        return -NotCreate;
    }

    if(index >= mSize || index < 0) {
        throw ArrayIndexOutOfBoundsException("fill Stack Overflow");
    }

    buff[index] = v;

    return 0;
}

int _ByteArray::fill(int index,int length,byte v) {
    if(buff == nullptr) {
        return -NotCreate;
    }

    if((index >= mSize) 
        || (index < 0)
        || (index + length > mSize)) {
        throw ArrayIndexOutOfBoundsException("fill Stack Overflow");
    }

    memset(&buff[index],v,length);

    return 0;
}

int _ByteArray::append(sp<_ByteArray> b) {
    if(b == nullptr) {
        return -InvalidParam;
    }
    return append(b->toValue(),b->size());
}

int _ByteArray::append(sp<_ByteArray>b,int len) {
    return append(b->toValue(),len);
}

int _ByteArray::append(byte *data,int len) {
    if(data == nullptr) {
        return -InvalidParam;
    }

    buff = (byte *)realloc(buff,mSize + len);
    memcpy(&buff[mSize],data,len);
    mSize += len;
    return mSize;
}

String _ByteArray::toString() {
    char _buff[mSize + 1];
    memset(_buff,0,mSize+1);
    memcpy(_buff,buff,mSize);
    return createString(&_buff[0],0,mSize + 1);
}

void _ByteArray::dump(const char *v) {
    printf("%s is : \n ",v);
    for(int i = 0;i < mSize;i++) {
        printf("0x%x ",this->buff[i]);
    }
}

void _ByteArray::dump(String v) {
    dump(v->toChars());
}

}
