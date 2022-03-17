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
    if (size <= 0) {
        Trigger(InitializeException, "size is invalid");
    }

    mCapacity = size;
    mSize = 0;
    mBuff = (byte *)malloc(size);
    mNext = 0;

    if (mBuff == nullptr) {
        Trigger(InitializeException, "alloc fail");
    }
}

_ByteRingArray::_ByteRingArray(sp<_ByteRingArray> data) {
    mCapacity = data->mCapacity;
    mSize = data->mSize;
    mNext = data->mNext;

    mBuff = (byte *)malloc(data->mCapacity);
    if (mBuff == nullptr) {
        Trigger(InitializeException, "alloc fail");
    }
    memcpy(mBuff, data->mBuff, mCapacity);
}

void _ByteRingArray::reset() {
    mSize = 0;
    mNext = 0;
    memset(mBuff, 0, mCapacity);
}

_ByteRingArray::~_ByteRingArray() {
    if (mBuff != nullptr) {
        free(mBuff);
        mBuff = nullptr;
    }
}

bool _ByteRingArray::push(byte b) {
    if (mSize == mCapacity) {
        Trigger(ArrayIndexOutOfBoundsException,"Ring Array push full Array!!!");
    }
    
    mBuff[mNext] = b;
    mSize++;
    mNext++;

    if (mNext == mCapacity) {
        mNext = 0;
    }
    return true;
}

byte _ByteRingArray::pop() {
    if (mSize == 0) {
        Trigger(ArrayIndexOutOfBoundsException,"Ring Array Pop Empty Array!!!");
    }

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
    if (length > (mCapacity - mSize)) {
        Trigger(ArrayIndexOutOfBoundsException, "Ring Array Push Overflow!!!");
    }
    
    if ((mNext + length) < mCapacity) {
        memcpy(mBuff + mNext, &array[start], length);
    } else {
        memcpy(mBuff + mNext, &array[start], mCapacity - mNext);
        memcpy(mBuff, &array[start + (mCapacity - mNext)], length - (mCapacity - mNext));
    }

    mNext += length;
    mSize += length;

    if (mNext >= mCapacity) {
        mNext = mNext - mCapacity;
    }
    return true;
}

ByteArray _ByteRingArray::pop(int size) {
    if (mSize < size || size == 0) {
        Trigger(IllegalArgumentException, "pop size error");
    }

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

// for ByteRingArrayReader,include end
ByteArray _ByteRingArray::popTo(int index) {
    int start = getStartIndex();
    int interval = (index - start) + 1;

    if (interval <= 0) {
        interval += mCapacity;
    }
    return pop(interval);
}

int _ByteRingArray::getAvailDataSize() { 
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
