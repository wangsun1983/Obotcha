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
        Trigger(InitializeException, "size is illeagle");
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
        Trigger(ArrayIndexOutOfBoundsException,
                "Ring Array push full Array!!!");
    }

    mBuff[mNext] = b;
    mSize++;
    if (mNext == (mCapacity - 1)) {
        mNext = 0;
    } else {
        mNext++;
    }
    return true;
}

byte _ByteRingArray::pop() {
    if (mSize == 0) {
        Trigger(ArrayIndexOutOfBoundsException,
                "Ring Array Pop Empty Array!!!");
    }

    int start = getStartIndex();
    byte c = mBuff[start];
    mSize--;
    return c;
}

bool _ByteRingArray::push(const ByteArray &data) {
    if (data == nullptr) {
        Trigger(IllegalArgumentException, "pop data is nullptr");
    }
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
        mNext += length;
    } else {
        int firstCopyLen = (mCapacity - mNext);
        memcpy(mBuff + mNext, &array[start], firstCopyLen);
        mNext += firstCopyLen;

        int secCopyLen = (length - firstCopyLen);
        if (secCopyLen != 0) {
            memcpy(mBuff, &array[start + firstCopyLen], secCopyLen);
            mNext += secCopyLen;
        }
    }

    if (mNext > mCapacity) {
        mNext = mNext - mCapacity;
    }

    mSize += length;

    return true;
}

ByteArray _ByteRingArray::pop(int size) {
    if (mSize <= 0) {
        Trigger(ArrayIndexOutOfBoundsException, "pop size is 0");
    }

    if (mSize < size) {
        Trigger(IllegalArgumentException, "pop size is illegal");
    }

    if (size == 0) {
        return nullptr;
    }

    int start = getStartIndex();
    ByteArray result = nullptr;
    if (start + size < mCapacity) {
        result = createByteArray(&mBuff[start], size);
    } else {
        result = createByteArray(size);
        int firstCopyLen = (mCapacity - start);
        memcpy(result->toValue(), mBuff + start, firstCopyLen);

        int secondCopyLen = size - firstCopyLen;
        memcpy(result->toValue() + firstCopyLen, mBuff, secondCopyLen);
    }
    mSize -= size;
    return result;
}

int _ByteRingArray::getNextIndex() { return mNext; }

void _ByteRingArray::setNextIndex(int n) { mNext = n; }

void _ByteRingArray::setSize(int s) { mSize = s; }

int _ByteRingArray::getCapacity() { return mCapacity; }

int _ByteRingArray::getStartIndex() {
    int start = mNext - mSize;
    if (start < 0) {
        start += mCapacity;
    }

    return start;
}

int _ByteRingArray::getEndIndex() { return mNext; }

byte _ByteRingArray::at(int m) { return mBuff[m]; }

ByteArray _ByteRingArray::popAll() { return pop(mSize); }

// for ByteRingArrayReader,include end
ByteArray _ByteRingArray::popTo(int index) {
    int interval = (mNext - index) - 1;
    if (interval < 0) {
        interval += mCapacity;
    }
    return pop(mSize - interval);
}

int _ByteRingArray::getAvailDataSize() { return mSize; }

// just for test
void _ByteRingArray::setStartIndex(int index) {
    int interval = (mNext - index);
    if (interval < 0) {
        interval += mCapacity;
    }

    mSize -= interval;
}

void _ByteRingArray::setEndIndex(int index) { mNext = index; }

} // namespace obotcha
