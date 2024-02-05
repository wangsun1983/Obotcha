/**
 * @file ByteRingArrayReader.cpp
 * @brief Provides low-level read access to a ring array.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include "ByteRingArrayReader.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

_ByteRingArrayReader::_ByteRingArrayReader(ByteRingArray b,st(IO)::Endianness endianess):
                                            mBuff(b),mEndianness(endianess) {
    mCursor = mBuff->getStartIndex();
}

ByteArray _ByteRingArrayReader::pop() {
    auto capacity = mBuff->getCapacity();    
    if(mCursor == mBuff->getStartIndex()) {
        return nullptr;
    }
    
    mCursor = mCursor % capacity;
    return mBuff->popTo((mCursor + capacity - 1) % capacity);
}

st(IO)::Reader::Result _ByteRingArrayReader::readNext(byte &value) {
    auto size = mBuff->getStoredDataSize();
    if (size == 0) {
        return st(IO)::Reader::Result::NoContent;
    }

    if(mCursor >= (mBuff->getStartIndex() + size)) {
        return st(IO)::Reader::Result::NoContent;
    }
    
    auto capacity = mBuff->getCapacity();
    value = mBuff->at(mCursor%capacity);
    mCursor++;
    return st(IO)::Reader::Result::HasContent;
}

void _ByteRingArrayReader::setCursor(size_t c) { 
    mCursor = c; 
}

size_t _ByteRingArrayReader::getCursor() const { 
    return mCursor; 
}

size_t _ByteRingArrayReader::move(size_t length) {
    if (length > mBuff->getStoredDataSize()) {
        Trigger(ArrayIndexOutOfBoundsException, "length is too large")
    }

    mCursor += length;
    return mCursor%mBuff->getCapacity();
}

size_t _ByteRingArrayReader::getReadableLength() const {
    auto storeSize = mBuff->getStoredDataSize();
    Inspect(storeSize == 0,0)

    auto startIndex = mBuff->getStartIndex();
    auto capacity = mBuff->getCapacity();
    auto read = (capacity + mCursor - startIndex)%capacity;
    return storeSize - read;
}

void _ByteRingArrayReader::reset() {
    mBuff->reset();
    mCursor = mBuff->getStartIndex();
}

} // namespace obotcha
