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
#include <fstream>
#include <stdio.h>

#include "ArrayIndexOutOfBoundsException.hpp"
#include "ByteArray.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"
#include "String.hpp"
#include "Inspect.hpp"

namespace obotcha {

const size_t _ByteArray::kDefaultSize = 32;

_ByteArray::_ByteArray():_ByteArray(kDefaultSize) {
};

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(sp<_ByteArray> &data, size_t start, size_t len) {
    Panic(data->isOverflow(start,len),InitializeException,"param is overflow")
    mSize = (len == 0)?data->size() - start:len;
    
    mPreviousSize = mSize;
    mBuff = (byte *)malloc(mSize);
    memcpy(mBuff, data->toValue() + start, mSize);
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(size_t length) {
    Panic(length == 0,InitializeException, "create ByteArray is nullptr")
    mBuff = (byte *)calloc(1,length);
    mPreviousSize = length;
    mSize = length;
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(byte *data, size_t len,bool mapped) {
    Panic(data == nullptr,InitializeException, "create ByteArray is nullptr")
    mMapped = mapped;
    mPreviousSize = len;
    mSize = len;

    if(!mapped) {
        mBuff = (byte *)calloc(1,len);
        memcpy(mBuff, data, len);
    } else {
        mBuff = data;
    }
}

/**
 * @brief clear memory data
 */
void _ByteArray::clear() {
    mSize = mPreviousSize;
    mStart = 0;
    memset(mBuff, 0, mSize);
}

byte &_ByteArray::operator[](size_t index) {
    Panic(index >= mSize,ArrayIndexOutOfBoundsException, 
          "size is %d,index is %d,mStart is %d \n",mSize,index,mStart)
    return mBuff[index + mStart];
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
        auto *v = (byte *)malloc(mSize);
        memcpy(v, mBuff + mStart, mSize);
        return v;
    }

    return mBuff + mStart;
}

size_t _ByteArray::size() const {
    return mSize;
}

int _ByteArray::quickShrink(size_t size) {
    Inspect(size >= mSize,-EINVAL)
    mSize = size;
    return 0;
}

size_t _ByteArray::quickRestore() {
    mSize = mPreviousSize;
    mStart = 0;
    return mSize;
}

int _ByteArray::growTo(size_t size) {
    Inspect(size <= mSize,-EINVAL)
    if(size > mPreviousSize - mStart) {
        mBuff = (byte *)realloc(mBuff, size + mStart);
        mPreviousSize = size + mStart;
    }

    memset(mBuff + mStart + mSize,0,size - mSize);
    mSize = size;
    return 0;
}

int _ByteArray::growBy(size_t size) {
    return growTo(mSize + size);
}

bool _ByteArray::isEmpty() const {
    return mSize == 0;
}

byte _ByteArray::at(size_t index) const {
    Panic(index >= mSize,ArrayIndexOutOfBoundsException, 
            "size is %d,index is %d,mStart is %dd \n",mSize,index,mStart)
    return mBuff[mStart + index];
}

int _ByteArray::fill(byte v) {
    memset(mBuff + mStart, v, mSize);
    return 0;
}

int _ByteArray::fill(size_t start, size_t length, byte v) {
    Panic(isOverflow(start,length),ArrayIndexOutOfBoundsException, 
            "fill Stack Overflow")
    memset(&mBuff[start + mStart], v, length);
    return 0;
}

int _ByteArray::fillFrom(const byte *input,size_t destStart,size_t len) {
    Panic(destStart + len > mSize,ArrayIndexOutOfBoundsException, 
        "fill Stack Overflow")

    memcpy(mBuff + destStart + mStart,input,len);
    return 0;
}

size_t _ByteArray::append(const sp<_ByteArray> &b) {
    Inspect(b == nullptr,-EINVAL)
    return append(b->toValue(), b->size());
}

size_t _ByteArray::append(const sp<_ByteArray> &b, size_t len) {
    Panic(b->size() < len,
            ArrayIndexOutOfBoundsException,
            "size is %d,len is %d",b->size(),len)
    return append(b->toValue(), len);
}

size_t _ByteArray::append(const byte *data, size_t len) {
    Inspect(data == nullptr || len == 0,-EINVAL)
    auto index = mSize + mStart;
    growBy(len);
    memcpy(&mBuff[index], data, len);
    return mSize;
}

String _ByteArray::toString() {
    char buff[mSize + 1];
    memcpy(buff, mBuff + mStart, mSize);
    buff[mSize] = 0;
    auto len = strlen(buff);
    return (len > 0)?createString(&buff[0], 0, len):nullptr;
}

void _ByteArray::dump(const char *v) const {
    printf("%s is : \n ", v);
    for (int i = 0; i < mSize; i++) {
        printf("0x%x ", this->mBuff[i + mStart]);
    }
    printf("\n");
}

void _ByteArray::dump(const String &v) const {
    dump(v->toChars());
}

void _ByteArray::dumpToFile(const char *path) const {
    std::ofstream fstream;
    fstream.open(path, std::ios::trunc);
    fstream.write((const char *)(mBuff + mStart), mSize);
    fstream.flush();
    fstream.close();
}

void _ByteArray::dumpToFile(const String &path) const {
    dumpToFile(path->toChars());
}

sp<_ByteArray> _ByteArray::clone() {
    return createByteArray(mBuff + mStart,mSize);
}

bool _ByteArray::equals(Object p) {
    auto v = dynamic_cast<_ByteArray *>(p.get_pointer());
    return (v == this) || (v!= nullptr &&v->size() == mSize 
                        && memcmp(mBuff + mStart,v->mBuff + v->mStart,mSize) == 0);
}

void _ByteArray::Combine(ByteArray &dest,ByteArray appenddata) {
    if(dest == nullptr) {
        dest = appenddata;
    } else {
        dest->append(appenddata);
    }
}

void _ByteArray::slice(size_t start,size_t length) {
    Panic(start >= mSize,ArrayIndexOutOfBoundsException,"transform")
    if(length == 0) {
        length = mSize - start;
    }
    
    Panic(isOverflow(start,length),ArrayIndexOutOfBoundsException,"transform")
    mStart = start;
    mSize = length;
}

bool _ByteArray::isOverflow(size_t start,size_t length) {
    return start >= mSize || start + length > mSize;
}

} // namespace obotcha
