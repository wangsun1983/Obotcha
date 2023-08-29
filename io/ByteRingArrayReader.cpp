/**
 * @file ByteArrayReader.cpp
 * @brief Byte Array Reader(support Little/Big Endian)
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
    switch(mMark) {
        case _ByteRingArrayReader::Mark::Complete: {
            mMark = _ByteRingArrayReader::Mark::Idle;
            return mBuff->popAll();
        }

        case _ByteRingArrayReader::Mark::Partial: {
            int index = mCursor - 1;
            if (index == -1) {
                index = mBuff->getCapacity() - 1;
            }
            mMark = _ByteRingArrayReader::Mark::Idle;
            return mBuff->popTo(index);
        }

        default:
        return nullptr;
    }
}

st(IO)::Reader::Result _ByteRingArrayReader::readNext(byte &value) {
    if (mBuff->getStoredDataSize() == 0) {
        return st(IO)::Reader::Result::NoContent;
    }

    int end = mBuff->getEndIndex();

    if (mCursor == end && mMark != _ByteRingArrayReader::Mark::Idle) {
        mMark = _ByteRingArrayReader::Mark::Complete;
        return st(IO)::Reader::Result::NoContent;
    }

    mMark = _ByteRingArrayReader::Mark::Partial;
    value = mBuff->at(mCursor);
    mCursor++;

    if (mCursor == mBuff->getCapacity()) {
        mCursor = 0;
    }

    return st(IO)::Reader::Result::HasContent;
}

void _ByteRingArrayReader::setCursor(int c) { 
    mCursor = c; 
}

int _ByteRingArrayReader::getCursor() const { 
    return mCursor; 
}

int _ByteRingArrayReader::move(int length) {
    if(length == 0) {
        return 0;
    }

    if (length > mBuff->getStoredDataSize()) {
        Trigger(ArrayIndexOutOfBoundsException, "length is too large")
    }

    mCursor += length;
    if (mCursor >= mBuff->getCapacity()) {
        mCursor = (mCursor - mBuff->getCapacity());
    }
    mMark = _ByteRingArrayReader::Mark::Partial;
    
    return mCursor;
}

int _ByteRingArrayReader::getReadableLength() const {
    if (mBuff->getStoredDataSize() == 0 
        || mMark == _ByteRingArrayReader::Mark::Complete) {
        return 0;
    }

    int end = mBuff->getEndIndex();
    if (mCursor > end) {
        return mBuff->getCapacity() - mCursor + end;
    } else if(mCursor == end && mMark == _ByteRingArrayReader::Mark::Idle){
        return mBuff->getCapacity();
    } else {
        return end - mCursor;
    }
}

void _ByteRingArrayReader::reset() {
    mBuff->reset();
    mCursor = mBuff->getStartIndex();
    mMark = _ByteRingArrayReader::Mark::Idle;
}

} // namespace obotcha
