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

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(sp<_ByteArray> b) {
    buff = (unsigned char *)malloc(b->size());
    memcpy(buff,b->toValue(),b->size());
    mSize = b->size();
    mCursor = 0;
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(int length) {
    buff = (unsigned char *)malloc(length);
    memset(buff,0,length);
    mSize = length;
    mCursor = 0;
}

/**
 * @brief ByteArray construct function
 * @param str save str as ByteArray
 */
_ByteArray::_ByteArray(String str) {
    int size = str->size();
    mSize = size;
    buff = (unsigned char *)malloc(mSize + 1);
    memset(buff,0,mSize + 1);
    memcpy(buff,str->toChars(),size);
    mCursor = 0;
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(const byte *data,int len) {
    buff = (unsigned char *)malloc(len);
    memset(buff,0,len);
    mSize = len;
    memcpy(buff,data,len);
    mCursor = 0;
}


/**
 * @brief clear memory data
 */
void _ByteArray::clear() {
    memset(buff,0,mSize);
    mCursor = 0;
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
    mCursor = 0;
}


byte *_ByteArray::toValue() {
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
    mCursor = 0;
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
    mCursor = 0;
    
    return 0;
}

bool _ByteArray::isEmpty() {
    return (buff == nullptr || mSize == 0);
}

byte _ByteArray::at(int index) {
    if(index >= mSize) {
        throw createArrayIndexOutOfBoundsException("ByteArray",mSize,index);
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
        return -InvalidParam;
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
        return -InvalidParam;
    }

    memset(&buff[index],v,length);

    return 0;
}

int _ByteArray::append(sp<_ByteArray> b) {
    printf("_ByteArray append trace1,b is %s,size is %d \n",b->toValue(),b->size());

    if(b == nullptr) {
        return -InvalidParam;
    }
    
    return append(b->toValue(),b->size());
}

int _ByteArray::append(byte *data,int len) {
    if(data == nullptr) {
        return -InvalidParam;
    }

    if((mCursor + len) <= mSize) {
        memcpy(&buff[mCursor],data,len);
        mCursor += len;
    }

    int oldCursor = mCursor;
    resize(mCursor + len);
    mCursor = oldCursor;
    memcpy(&buff[mCursor],data,len);
}

String _ByteArray::toString() {
    char _buff[mSize + 1];
    memset(_buff,0,mSize+1);
    memcpy(_buff,buff,mSize);
    return createString(&_buff[0],0,mSize + 1);
}

}
