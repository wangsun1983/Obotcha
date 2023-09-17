#include "ArrayIndexOutOfBoundsException.hpp"
#include "ByteRingArray.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_ByteRingArray::_ByteRingArray(size_t size):mCapacity(size) {
    mBuff = (byte *)zmalloc(size);
}

_ByteRingArray::_ByteRingArray(sp<_ByteRingArray> data):_ByteRingArray(data->mSize) {
    mNext = data->mNext;
    mSize = data->mSize;
    memcpy(mBuff,data->mBuff,mSize);
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
    Panic(mSize == mCapacity,ArrayIndexOutOfBoundsException,
            "Ring Array push full Array!!!")

    mBuff[mNext] = b;
    mSize++;
    mNext++;
    if (mNext == mCapacity) {
        mNext = 0;
    }
    return true;
}

byte _ByteRingArray::pop() {
    Panic(mSize == 0,
        ArrayIndexOutOfBoundsException,"Ring Array Pop Empty Array!!!")
    size_t start = getStartIndex();
    mSize--;
    return mBuff[start];
}

bool _ByteRingArray::push(const ByteArray &data) {
    return push(data, 0, data->size());
}

bool _ByteRingArray::push(const ByteArray &array, size_t start, size_t length) {
    return push(array->toValue(), start, length);
}

bool _ByteRingArray::push(const byte *array, size_t start, size_t length) {
    Panic(length > (mCapacity - mSize),
        ArrayIndexOutOfBoundsException,"Ring Array Push Overflow!!!")

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

ByteArray _ByteRingArray::pop(size_t size) {
    Panic(mSize < size || size == 0,IllegalArgumentException, "pop size error")
    size_t start = getStartIndex();
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

size_t _ByteRingArray::getNextIndex() const {
    return mNext;
}

void _ByteRingArray::setNextIndex(size_t n) {
    mNext = n;
}

void _ByteRingArray::setSize(size_t s) {
    mSize = s;
}

size_t _ByteRingArray::getCapacity() const {
    return mCapacity;
}

size_t _ByteRingArray::getStartIndex() const {
    size_t start = 0;
    if(mNext >= mSize) {
        start = mNext - mSize;
    } else {
        start = mCapacity + mNext - mSize;
    }
    return start;
}

size_t _ByteRingArray::getEndIndex() const {
    return mNext;
}

byte _ByteRingArray::at(size_t m) const {
    return mBuff[m];
}

ByteArray _ByteRingArray::popAll() {
    return pop(mSize);
}

void _ByteRingArray::dump(const char *tag) const {
    if(tag != nullptr) {
        printf("ByteRingArry dump,%s is : \n ", tag);
    }
    size_t start = getStartIndex();
    size_t end = getEndIndex();
    
    while(start != end) {
        printf("data[%lu] is %x \n",start,mBuff[start]);
        start++;
        if(start == mCapacity) {
            start = 0;
        }
    }
}

void _ByteRingArray::dumpFull(const char * tag) const {
    if(tag != nullptr) {
        printf("ByteRingArry dump,%s is : \n ", tag);
    }

    for(int i = 0; i < mCapacity;i++) {
        printf("data[%d] is %x \n",i,mBuff[i]);
    }
}

// for ByteRingArrayReader,include end
ByteArray _ByteRingArray::popTo(size_t index) {
    size_t start = getStartIndex();
    size_t interval = 0;
    if (index + 1 <= start) {
        interval = (index - start) + 1 + mCapacity;
    } else {
        interval = (index - start) + 1;
    }
    return pop(interval);
}

size_t _ByteRingArray::getStoredDataSize() const {
    return mSize;
}

// just for test
void _ByteRingArray::setStartIndex(size_t index) {
    auto interval = (mNext < index)?mCapacity + mNext - index:mNext - index;
    mSize -= interval;
}

void _ByteRingArray::setEndIndex(size_t index) {
    mNext = index;
}

} // namespace obotcha
