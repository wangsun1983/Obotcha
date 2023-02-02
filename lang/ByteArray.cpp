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

namespace obotcha {

const int _ByteArray::DefaultSize = 32;

_ByteArray::_ByteArray():_ByteArray(DefaultSize) {

};

/**
 * @brief ByteArray construct function
 * @param b copy value
 */
_ByteArray::_ByteArray(sp<_ByteArray> &data, int start, int len) {
    int malloc_size = (len == 0) ? data->size() - start : len;

    if (malloc_size > data->size() - start || malloc_size <= 0) {
        Trigger(InitializeException, "create ByteArray overflow");
    }

    buff = (unsigned char *)malloc(malloc_size);
    mSize = malloc_size;
    memcpy(buff, data->toValue() + start, malloc_size);
    mOriginalSize = -1;
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param length alloc memory size
 */
_ByteArray::_ByteArray(int length) {
    if (length <= 0) {
        Trigger(InitializeException, "create ByteArray is nullptr");
    }

    buff = (unsigned char *)malloc(length);
    memset(buff, 0, length);

    mSize = length;
    mOriginalSize = -1;
    mMapped = false;
}

/**
 * @brief ByteArray construct function
 * @param data source data
 * @param len save data len
 */
_ByteArray::_ByteArray(const byte *data, uint32_t len,bool mapped) {
    if (data == nullptr) {
        Trigger(InitializeException, "create ByteArray is nullptr");
    }

    mMapped = mapped;
    mSize = len;
    if(!mapped) {
        buff = (unsigned char *)malloc(len);
        memcpy(buff, data, len);
    } else {
        buff = (unsigned char *)data;
    }

    mOriginalSize = -1;
}

/**
 * @brief clear memory data
 */
void _ByteArray::clear() {
    if (mOriginalSize != -1) {
        mSize = mOriginalSize;
    }
    memset(buff, 0, mSize);
    mOriginalSize = -1;
}

byte &_ByteArray::operator[](int index) {
    if (index >= mSize || index < 0) {
        Trigger(ArrayIndexOutOfBoundsException, "size is %d,index is %d \n",mSize,index);
    }

    return buff[index];
}

/**
 * @brief ByteArray destruct function
 */
_ByteArray::~_ByteArray() {
    if (buff != nullptr && !mMapped) {
        free(buff);
        buff = nullptr;
    }

    mSize = 0;
}

byte *_ByteArray::toValue(bool copy) {
    if (copy) {
        byte *v = (byte *)malloc(mSize);
        memcpy(v, buff, mSize);
        return v;
    }

    return buff;
}

int _ByteArray::size() {
    return mSize;
}

int _ByteArray::quickShrink(int size) {
    if (size >= mSize || size < 0) {
        return -EINVAL;
    }

    buff[size] = 0;
    if(mOriginalSize == -1) {
        mOriginalSize = mSize;
    }
    mSize = size;
    return 0;
}

int _ByteArray::quickRestore() {
    if (mOriginalSize == -1) {
        return -1;
    }
    mSize = mOriginalSize;
    mOriginalSize = -1;
    return mSize;
}

int _ByteArray::growTo(int size) {
    if (size <= mSize) {
        return -EINVAL;
    }

    int len = size - mSize;
    if (size <= this->mOriginalSize) {
        memset(buff + mSize, 0, len);
        mSize = size;
        return mSize;
    }

    byte *ptr = (byte *)realloc(buff, size);
    if (ptr == nullptr) {
        Trigger(OutOfMemoryException, "alloc failed");
    }
    memset(ptr + mSize, 0, len);

    buff = ptr;
    mSize = size;
    return mSize;
}

int _ByteArray::growBy(int size) {
    return growTo(mSize + size);
}

bool _ByteArray::isEmpty() {
  return mSize == 0;
}

byte _ByteArray::at(int index) {
    if (index >= mSize || index < 0) {
        Trigger(ArrayIndexOutOfBoundsException, "size is %d,index is %d \n",mSize,index);
    }
    return buff[index];
}

int _ByteArray::fill(byte v) {
    memset(buff, v, mSize);
    return 0;
}

int _ByteArray::fill(int start, int length, byte v) {
    if ((start < 0) || (start + length > mSize)) {
        Trigger(ArrayIndexOutOfBoundsException, "fill Stack Overflow");
    }

    memset(&buff[start], v, length);

    return 0;
}

int _ByteArray::fillFrom(byte *input,int start,int len) {
    if ((start < 0) || (start + len > mSize)) {
        Trigger(ArrayIndexOutOfBoundsException, "fill Stack Overflow");
    }

    memcpy(buff + start,input,len);
    return 0;
}

int _ByteArray::append(const sp<_ByteArray> &b) {
    if (b == nullptr) {
        return -EINVAL;
    }
    return append(b->toValue(), b->size());
}

int _ByteArray::append(const sp<_ByteArray> &b, int len) {
    if(b->size() < len) {
        Trigger(ArrayIndexOutOfBoundsException,"size is %d,len is %d",b->size(),len);
    }
    return append(b->toValue(), len);
}

int _ByteArray::append(byte *data, int len) {
    if (data == nullptr || len <= 0) {
        return -EINVAL;
    }

    int currentSize = mSize;
    growBy(len);
    memcpy(&buff[currentSize], data, len);
    return mSize;
}

String _ByteArray::toString() {
    int len = mSize + 1;
    char _buff[len];
    memcpy(_buff, buff, mSize);
    _buff[len - 1] = 0;
    return createString(&_buff[0], 0, strlen(_buff));
}

void _ByteArray::dump(const char *v) {
    printf("%s is : \n ", v);
    for (int i = 0; i < mSize; i++) {
        printf("0x%x ", this->buff[i]);
    }
    printf("\n");
}

void _ByteArray::dump(const String &v) {
  dump(v->toChars());
}

void _ByteArray::dumpToFile(const char *path) {
    std::ofstream fstream;
    fstream.open(path, std::ios::trunc);
    fstream.write((const char *)buff, mSize);
    fstream.flush();
    fstream.close();
}

void _ByteArray::dumpToFile(const String &path) {
  dumpToFile(path->toChars());
}

sp<_ByteArray> _ByteArray::clone() {
    ByteArray array = createByteArray(mSize);
    memcpy(array->buff,buff,mSize);
    return array;
}

bool _ByteArray::equals(const ByteArray &s) {
    if(s == nullptr || s->size() != mSize) {
        return false;
    }

    return (this == s.get_pointer()) || (memcmp(buff,s->buff,mSize) == 0);
}

} // namespace obotcha
