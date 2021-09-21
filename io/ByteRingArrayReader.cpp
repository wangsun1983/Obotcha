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

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayIndexOutOfBoundsException.hpp"
#include "ByteArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "Error.hpp"
#include "String.hpp"

namespace obotcha {

_ByteRingArrayReader::_ByteRingArrayReader(ByteRingArray b) {
    mBuff = b;
    mCursor = mBuff->getStartIndex();
    mMark = Idle;
}

ByteArray _ByteRingArrayReader::pop() {
    ByteArray result = nullptr;

    try {
        if (mMark == Complete) {
            result = mBuff->popAll();
            mMark = Idle;
        } else {
            int index = mCursor - 1;
            if (index == -1) {
                index = mBuff->getCapacity() - 1;
            }
            result = mBuff->popTo(index);
        }
    } catch (ArrayIndexOutOfBoundsException &e) {
    }

    return result;
}

int _ByteRingArrayReader::readNext(byte &value) {
    if (mBuff->getAvailDataSize() == 0) {
        return NoContent;
    }

    int end = mBuff->getEndIndex();

    if (mCursor == end) {
        if (mMark != Idle) {
            mMark = Complete;
            return NoContent;
        }
    }

    mMark = Partial;
    value = mBuff->at(mCursor);
    mCursor++;

    if (mCursor == mBuff->getCapacity()) {
        mCursor = 0;
    }

    return Continue;
}

void _ByteRingArrayReader::setCursor(int c) { mCursor = c; }

int _ByteRingArrayReader::getCursor() { return mCursor; }

int _ByteRingArrayReader::move(int length) {
    if (length > mBuff->getAvailDataSize()) {
        Trigger(ArrayIndexOutOfBoundsException, "length is too large");
    }

    mCursor += length;
    if (mCursor >= mBuff->getCapacity()) {
        mCursor = (mCursor - mBuff->getCapacity());
    }

    return mCursor;
}

int _ByteRingArrayReader::getReadableLength() {
    if (mBuff->getAvailDataSize() == 0) {
        return 0;
    }

    int end = mBuff->getEndIndex();

    if (mCursor >= end) {
        return mBuff->getAvailDataSize() - (mCursor - end);
    } else {
        return end - mCursor;
    }
}

void _ByteRingArrayReader::reset() {
    mBuff->reset();
    mCursor = mBuff->getStartIndex();
    mMark = Idle;
}

} // namespace obotcha
