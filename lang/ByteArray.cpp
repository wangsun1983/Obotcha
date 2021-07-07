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
#include <stdio.h>

#include "Error.hpp"
#include "ByteArray.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "InitializeException.hpp"
#include "String.hpp"

namespace obotcha {

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(const sp<_ByteArray> &b,bool isSafe) {
    if(b == nullptr || b->size() <= 0) {
        Trigger(InitializeException,"create ByteArray is nullptr");
    }
    mSize = b->size();
    buff = (unsigned char *)malloc(mSize);
    memcpy(buff,b->toValue(),mSize);
    this->isSafe = isSafe;
    mOriginalSize = -1;
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(int length,bool isSafe) {
    if(length <= 0) {
        Trigger(InitializeException,"create ByteArray is nullptr");
    }
    buff = (unsigned char *)malloc(length);
    memset(buff,0,length);
    mSize = length;
    this->isSafe = isSafe;
    mOriginalSize = -1;
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(const byte *data,uint32_t len,bool isSafe) {
    if(data == nullptr) {
        Trigger(InitializeException,"create ByteArray is nullptr");
    }
    buff = (unsigned char *)malloc(len);
    mSize = len;
    memcpy(buff,data,len);
    this->isSafe = isSafe;
    mOriginalSize = -1;
}

/**
 * @brief clear memory data
 */
void _ByteArray::clear() {
    if(mOriginalSize != -1) {
        mSize = mOriginalSize;    
    }
    memset(buff,0,mSize);
    mOriginalSize = -1;
}

byte & _ByteArray::operator[] (int index) {
    if(index >= mSize) {
        String exception = createString("ByteArray [] fail")
                            ->append("size is",
                                    createString(mSize),
                                    "index is ",
                                    createString(index));

        Trigger(ArrayIndexOutOfBoundsException,exception);
    }
    
    return buff[index];
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
    if(isSafe) {
        byte *v = (byte*)malloc(mSize);
        memcpy(v,buff,mSize);
        return v;
    }
    
    return buff;
}

int _ByteArray::size() {
    return mSize;
}

int _ByteArray::quickShrink(int size) {
    if(size >= mSize) {
        return -InvalidParam;
    }

    buff[size] = 0;
    mOriginalSize = mSize;
    mSize = size;
    return 0;
}

int _ByteArray::quickRestore() {
    if(mOriginalSize == -1) {
        return -1;
    }
    mSize = mOriginalSize;
    mOriginalSize = -1;
    return mSize;
}

int _ByteArray::growTo(int size) {
    if(size <= mSize) {
        return -InvalidParam;
    }

    buff = (byte *)realloc(buff,size);

    mSize = size;    
    
    return 0;
}

int _ByteArray::growBy(int size) {
    if(size <= 0) {
        return -InvalidParam;
    }

    mSize += size;

    buff = (byte *)realloc(buff,mSize);

    return 0;
}

bool _ByteArray::isEmpty() {
    return mSize == 0;
}

byte _ByteArray::at(int index) {
    if(index >= mSize) {
        String exception = createString("ByteArray at fail")
                            ->append("size is",
                                    createString(mSize),
                                    "index is ",
                                    createString(index));

        Trigger(ArrayIndexOutOfBoundsException,exception);
    }
    return buff[index];
}

int _ByteArray::fill(byte v) {
    memset(buff,v,mSize);
    return 0;
}

int _ByteArray::fill(int index,byte v) {

    if(index >= mSize || index < 0) {
        Trigger(ArrayIndexOutOfBoundsException,"fill Stack Overflow");
    }

    buff[index] = v;

    return 0;
}

int _ByteArray::fill(int index,int length,byte v) {
    if((index < 0)
        || (index + length > mSize)) {
        Trigger(ArrayIndexOutOfBoundsException,"fill Stack Overflow");
    }

    memset(&buff[index],v,length);

    return 0;
}

int _ByteArray::append(const sp<_ByteArray> &b) {
    if(b == nullptr) {
        return -InvalidParam;
    }
    return append(b->toValue(),b->size());
}

int _ByteArray::append(const sp<_ByteArray> &b,int len) {
    return append(b->toValue(),len);
}

int _ByteArray::append(byte *data,int len) {
    if(data == nullptr || len <= 0) {
        return -InvalidParam;
    }

    buff = (byte *)realloc(buff,mSize + len);
    memcpy(&buff[mSize],data,len);
    mSize += len;
    return mSize;
}

String _ByteArray::toString() {
    int len = mSize;
    if(buff[mSize - 1] != 0) {
        len += 1;
    }

    char _buff[len];
    memcpy(_buff,buff,mSize);
    _buff[len - 1] = 0;
    return createString(&_buff[0],0,len);
}

void _ByteArray::dump(const char *v) {
    printf("%s is : \n ",v);
    for(int i = 0;i < mSize;i++) {
        printf("0x%x ",this->buff[i]);
    }
    printf("\n");
}

void _ByteArray::dump(const String &v) {
    dump(v->toChars());
}

void _ByteArray::dumpToFile(const char *path) {
    std::ofstream fstream;
    fstream.open(path,std::ios::trunc);
    fstream.write((const char *)buff,mSize);
    fstream.flush();
    fstream.close();
}

void _ByteArray::dumpToFile(const String &path) {
    dumpToFile(path->toChars());
}

}
