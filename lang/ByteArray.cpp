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
#include "String.hpp"
#include "Inspect.hpp"

namespace obotcha {

const uint64_t _ByteArray::kDefaultSize = 32;

_ByteArray::_ByteArray():_ByteArray(kDefaultSize) {
};

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(sp<_ByteArray> &data, uint64_t start, uint64_t len) {
    if(len == 0) {
        Panic(data->size() <= start,InitializeException,"start more than size")
        mSize = data->size() - start;
    } else {
        Panic(data->size() < start + len,InitializeException,"size less than start+len")
        mSize = len;
    }

    mPreviousSize = mSize;
    mBuff = (byte *)malloc(mSize);
    memcpy(mBuff, data->toValue() + start, mSize);
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(uint64_t length) {
    Panic(length == 0,InitializeException, "create ByteArray is nullptr")
    mBuff = (byte *)zmalloc(length);
    mPreviousSize = length;
    mSize = length;
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(byte *data, uint64_t len,bool mapped) {
    Panic(data == nullptr,InitializeException, "create ByteArray is nullptr")
    mMapped = mapped;
    mPreviousSize = len;
    mSize = len;

    if(!mapped) {
        mBuff = (byte *)zmalloc(len);
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
    memset(mBuff, 0, mSize);
}

byte &_ByteArray::operator[](uint64_t index) {
    Panic(index >= mSize,ArrayIndexOutOfBoundsException, 
          "size is %d,index is %d \n",mSize,index)
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
        auto *v = (byte *)malloc(mSize);
        memcpy(v, mBuff, mSize);
        return v;
    }

    return mBuff;
}

uint64_t _ByteArray::size() const {
    return mSize;
}

int _ByteArray::quickShrink(uint64_t size) {
    Inspect(size >= mSize,-EINVAL)
    mSize = size;
    return 0;
}

int _ByteArray::quickRestore() {
    mSize = mPreviousSize;
    return mSize;
}

int _ByteArray::growTo(uint64_t size) {
    Inspect(size <= mSize,-EINVAL)

    if(size > mPreviousSize) {
        mBuff = (byte *)realloc(mBuff, size);
        mPreviousSize = size;
    }

    memset(mBuff + mSize,0,size - mSize);
    mSize = size;
    return 0;
}

int _ByteArray::growBy(uint64_t size) {
    return growTo(mSize + size);
}

bool _ByteArray::isEmpty() const {
    return mSize == 0;
}

byte _ByteArray::at(uint64_t index) const {
    Panic(index >= mSize,ArrayIndexOutOfBoundsException, 
            "size is %d,index is %d \n",mSize,index)
    return mBuff[index];
}

int _ByteArray::fill(byte v) {
    memset(mBuff, v, mSize);
    return 0;
}

int _ByteArray::fill(uint64_t start, uint64_t length, byte v) {
    Panic(start + length > mSize,ArrayIndexOutOfBoundsException, 
            "fill Stack Overflow")
    memset(&mBuff[start], v, length);
    return 0;
}

int _ByteArray::fillFrom(const byte *input,uint64_t destStart,uint64_t len) {
    Panic(destStart + len > mSize,ArrayIndexOutOfBoundsException, 
        "fill Stack Overflow")

    memcpy(mBuff + destStart,input,len);
    return 0;
}

uint64_t _ByteArray::append(const sp<_ByteArray> &b) {
    Inspect(b == nullptr,-EINVAL)
    return append(b->toValue(), b->size());
}

uint64_t _ByteArray::append(const sp<_ByteArray> &b, uint64_t len) {
    Panic(b->size() < len,
            ArrayIndexOutOfBoundsException,
            "size is %d,len is %d",b->size(),len)
    return append(b->toValue(), len);
}

uint64_t _ByteArray::append(const byte *data, uint64_t len) {
    Inspect(data == nullptr || len == 0,-EINVAL)
    int index = mSize;
    growBy(len);
    memcpy(&mBuff[index], data, len);
    return mSize;
}

String _ByteArray::toString() {
    char buff[mSize + 1];
    memcpy(buff, mBuff, mSize);
    buff[mSize] = 0;
    auto len = strlen(buff);
    return (len > 0)?createString(&buff[0], 0, len):nullptr;
}

void _ByteArray::dump(const char *v) const {
    printf("%s is : \n ", v);
    for (int i = 0; i < mSize; i++) {
        printf("0x%x ", this->mBuff[i]);
    }
    printf("\n");
}

void _ByteArray::dump(const String &v) const {
    dump(v->toChars());
}

void _ByteArray::dumpToFile(const char *path) const {
    std::ofstream fstream;
    fstream.open(path, std::ios::trunc);
    fstream.write((const char *)mBuff, mSize);
    fstream.flush();
    fstream.close();
}

void _ByteArray::dumpToFile(const String &path) const {
    dumpToFile(path->toChars());
}

sp<_ByteArray> _ByteArray::clone() {
    return createByteArray(mBuff,mSize);
}

bool _ByteArray::equals(Object p) {
    auto v = dynamic_cast<_ByteArray *>(p.get_pointer());
    return (v == this) || (v!= nullptr &&v->size() == mSize 
                        && memcmp(mBuff,v->mBuff,mSize) == 0);
}

void _ByteArray::Combine(ByteArray &dest,ByteArray appenddata) {
    if(dest == nullptr) {
        dest = appenddata;
    } else {
        dest->append(appenddata);
    }
}

} // namespace obotcha
