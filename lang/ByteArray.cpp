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

#include "ArrayIndexOutOfBoundsException.hpp"
#include "ByteArray.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "OutOfMemoryException.hpp"
#include "String.hpp"
#include "Inspect.hpp"

namespace obotcha {

const int _ByteArray::kDefaultSize = 32;

_ByteArray::_ByteArray():_ByteArray(kDefaultSize) {

};

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(sp<_ByteArray> &data, int start, int len) {
    mSize = (len == 0)?data->size() - start:len;
    mPreviousSize = mSize;
    Panic(mSize > (data->size() - start),InitializeException, "create ByteArray overflow");

    mBuff = (unsigned char *)malloc(mSize);
    memcpy(mBuff, data->toValue() + start, mSize);
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(int length) {
    Panic(length <= 0,InitializeException, "create ByteArray is nullptr");
    mBuff = (unsigned char *)zmalloc(length);
    mPreviousSize = mSize = length;
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(const byte *data, uint32_t len,bool mapped) {
    Panic(data == nullptr,InitializeException, "create ByteArray is nullptr");
    mMapped = mapped;
    mPreviousSize = mSize = len;
    if(!mapped) {
        mBuff = (unsigned char *)zmalloc(len);
        memcpy(mBuff, data, len);
    } else {
        mBuff = (unsigned char *)data;
    }
}

/**
 * @brief clear memory data
 */
void _ByteArray::clear() {
    mSize = mPreviousSize;
    memset(mBuff, 0, mSize);
}

byte &_ByteArray::operator[](int index) {
    Panic(index >= mSize || index < 0,ArrayIndexOutOfBoundsException, 
          "size is %d,index is %d \n",mSize,index);
    return mBuff[index];
}

/**
 * @brief ByteArray destruct function
 */
_ByteArray::~_ByteArray() {
    if (mBuff != nullptr && !mMapped) {
        free(mBuff);
        mBuff = nullptr;
    }

    mSize = 0;
}

byte *_ByteArray::toValue(bool copy) {
    if (copy) {
        byte *v = (byte *)malloc(mSize);
        memcpy(v, mBuff, mSize);
        return v;
    }

    return mBuff;
}

int _ByteArray::size() {
    return mSize;
}

int _ByteArray::quickShrink(int size) {
    Inspect(size >= mSize || size < 0,-EINVAL);
    mSize = size;
    return 0;
}

int _ByteArray::quickRestore() {
    //memset(mBuff + mSize,0,mPreviousSize - mSize);
    mSize = mPreviousSize;
    return mSize;
}

int _ByteArray::growTo(int size) {
    Inspect(size <= mSize,-EINVAL);

    if(size <= mPreviousSize) {
        memset(mBuff + mSize,0,size - mSize);
    } else {
        mBuff = (byte *)realloc(mBuff, size);
        memset(mBuff + mSize, 0, size - mSize);
        mPreviousSize = size;
    }

    mSize = size;
    return 0;
}

int _ByteArray::growBy(int size) {
    return growTo(mSize + size);
}

bool _ByteArray::isEmpty() {
    return mSize == 0;
}

byte _ByteArray::at(int index) {
    Panic(index >= mSize || index < 0,ArrayIndexOutOfBoundsException, 
            "size is %d,index is %d \n",mSize,index);
    return mBuff[index];
}

int _ByteArray::fill(byte v) {
    memset(mBuff, v, mSize);
    return 0;
}

int _ByteArray::fill(int start, int length, byte v) {
    Panic((start < 0) || (start + length > mSize),ArrayIndexOutOfBoundsException, 
            "fill Stack Overflow");
    memset(&mBuff[start], v, length);
    return 0;
}

int _ByteArray::fillFrom(byte *input,int destStart,int len) {
    Panic((destStart < 0) || (destStart + len > mSize),
        ArrayIndexOutOfBoundsException, 
        "fill Stack Overflow");

    memcpy(mBuff + destStart,input,len);
    return 0;
}

int _ByteArray::append(const sp<_ByteArray> &b) {
    Inspect(b == nullptr,-EINVAL);
    return append(b->toValue(), b->size());
}

int _ByteArray::append(const sp<_ByteArray> &b, int len) {
    Panic(b->size() < len,
            ArrayIndexOutOfBoundsException,
            "size is %d,len is %d",b->size(),len);
    return append(b->toValue(), len);
}

int _ByteArray::append(byte *data, int len) {
    Inspect(data == nullptr || len <= 0,-EINVAL);
    int index = mSize;
    growBy(len);
    memcpy(&mBuff[index], data, len);
    return mSize;
}

String _ByteArray::toString() {
    char buff[mSize + 1];
    memcpy(buff, mBuff, mSize);
    buff[mSize] = 0;
    int len = strlen(buff);
    return (len > 0)?createString(&buff[0], 0, len):nullptr;
}

void _ByteArray::dump(const char *v) {
    printf("%s is : \n ", v);
    for (int i = 0; i < mSize; i++) {
        printf("0x%x ", this->mBuff[i]);
    }
    printf("\n");
}

void _ByteArray::dump(const String &v) {
    dump(v->toChars());
}

void _ByteArray::dumpToFile(const char *path) {
    std::ofstream fstream;
    fstream.open(path, std::ios::trunc);
    fstream.write((const char *)mBuff, mSize);
    fstream.flush();
    fstream.close();
}

void _ByteArray::dumpToFile(const String &path) {
    dumpToFile(path->toChars());
}

sp<_ByteArray> _ByteArray::clone() {
    ByteArray array = createByteArray(mSize);
    memcpy(array->mBuff,mBuff,mSize);
    return array;
}

bool _ByteArray::equals(const ByteArray &s) {
    Inspect(s == nullptr || s->size() != mSize,false);
    return this == s.get_pointer() || memcmp(mBuff,s->mBuff,mSize) == 0;
}

void _ByteArray::Combine(ByteArray &dest,ByteArray appenddata) {
    if(dest == nullptr) {
        dest = appenddata;
    } else {
        dest->append(appenddata);
    }
}


} // namespace obotcha
