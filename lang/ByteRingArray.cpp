#include <math.h>
#include <memory.h>
#include <stdlib.h>

#include "ArrayIndexOutOfBoundsException.hpp"
#include "ByteRingArray.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

_ByteRingArray::_ByteRingArray(int size) {
    Panic(size <= 0,InitializeException, "size is invalid");
    mCapacity = size;
    mSize = mNext = 0;
    mBuff = (byte *)zmalloc(size);
}

_ByteRingArray::_ByteRingArray(sp<_ByteRingArray> data) {
    mCapacity = data->mCapacity;
    mSize = data->mSize;
    mNext = data->mNext;
    mBuff = (byte *)zmalloc(data->mCapacity);
    memcpy(mBuff,data->mBuff,mSize);
}

void _ByteRingArray::reset() {
    mSize = mNext = 0;
    memset(mBuff, 0, mCapacity);
}

_ByteRingArray::~_ByteRingArray() {
    if (mBuff != nullptr) {
        free(mBuff);
        mBuff = nullptr;
    }
}

bool _ByteRingArray::push(byte b) {
    Panic(mSize == mCapacity,
            ArrayIndexOutOfBoundsException,
            "Ring Array push full Array!!!");

    mBuff[mNext] = b;
    mSize++;
    if (++mNext == mCapacity) {
        mNext = 0;
    }
    return true;
}

byte _ByteRingArray::pop() {
    Panic(mSize == 0,
        ArrayIndexOutOfBoundsException,"Ring Array Pop Empty Array!!!");
    int start = getStartIndex();
    mSize--;
    return mBuff[start];
}

bool _ByteRingArray::push(const ByteArray &data) {
    return push(data, 0, data->size());
}

bool _ByteRingArray::push(const ByteArray &array, int start, int length) {
    return push(array->toValue(), start, length);
}

bool _ByteRingArray::push(byte *array, int start, int length) {
    Panic(length > (mCapacity - mSize),
        ArrayIndexOutOfBoundsException,"Ring Array Push Overflow!!!");

    if ((mNext + length) < mCapacity) {
        memcpy(mBuff + mNext, &array[start], length);
    } else {
        memcpy(mBuff + mNext, &array[start], mCapacity - mNext);
        memcpy(mBuff, &array[start + (mCapacity - mNext)], length - (mCapacity - mNext));
    }

    mSize += length;

    if ((mNext += length) >= mCapacity) {
        mNext = mNext - mCapacity;
    }
    return true;
}

ByteArray _ByteRingArray::pop(int size) {
    Panic(mSize < size || size == 0,IllegalArgumentException, "pop size error");
    int start = getStartIndex();
    ByteArray result = createByteArray(size);
    if ((start + size) < mCapacity) {
        memcpy(result->toValue(), mBuff + start, size);
    } else {
        memcpy(result->toValue(), mBuff + start, mCapacity - start);
        memcpy(result->toValue() + (mCapacity - start), mBuff, size - (mCapacity - start));
    }

    mSize -= size;
    return result;
}

int _ByteRingArray::getNextIndex() {
    return mNext;
}

void _ByteRingArray::setNextIndex(int n) {
    mNext = n;
}

void _ByteRingArray::setSize(int s) {
    mSize = s;
}

int _ByteRingArray::getCapacity() {
    return mCapacity;
}

int _ByteRingArray::getStartIndex() {
    int start = mNext - mSize;
    return (start < 0)?start += mCapacity:start;
}

int _ByteRingArray::getEndIndex() {
    return mNext;
}

byte _ByteRingArray::at(int m) {
    return mBuff[m];
}

ByteArray _ByteRingArray::popAll() {
    return pop(mSize);
}

void _ByteRingArray::dump(const char *tag) {
    if(tag != nullptr) {
        printf("ByteRingArry dump,%s is : \n ", tag);
    }
    int start = getStartIndex();
    int end = getEndIndex();
    
    while(start != end) {
        printf("data[%d] is %x \n",start,mBuff[start]);
        start++;
        if(start == mCapacity) {
            start = 0;
        }
    }
}


void _ByteRingArray::dumpFull(const char * tag) {
    if(tag != nullptr) {
        printf("ByteRingArry dump,%s is : \n ", tag);
    }

    for(int i = 0; i < mCapacity;i++) {
        printf("data[%d] is %x \n",i,mBuff[i]);
    }
}

// for ByteRingArrayReader,include end
ByteArray _ByteRingArray::popTo(int index) {
    int start = getStartIndex();
    int interval = (index - start) + 1;

    if (interval <= 0) {
        interval += mCapacity;
    }
    return pop(interval);
}

int _ByteRingArray::getStoredDataSize() {
    return mSize;
}

// just for test
void _ByteRingArray::setStartIndex(int index) {
    int interval = (mNext - index);
    if (interval < 0) {
        interval += mCapacity;
    }

    mSize -= interval;
}

void _ByteRingArray::setEndIndex(int index) {
    mNext = index;
}

} // namespace obotcha
