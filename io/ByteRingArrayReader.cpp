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

_ByteRingArrayReader::_ByteRingArrayReader(ByteRingArray b,int mod) {
    mBuff = b;
    mCursor = mBuff->getStartIndex();
    mMark = Idle;
    mMode = mod;
}

ByteArray _ByteRingArrayReader::pop() {
    switch(mMark) {
        case Complete: {
            mMark = Idle;
            return mBuff->popAll();
        }

        case Partial: {
            int index = mCursor - 1;
            if (index == -1) {
                index = mBuff->getCapacity() - 1;
            }
            mMark = Idle;
            return mBuff->popTo(index);
        }
    }

    return nullptr;
}

int _ByteRingArrayReader::readNext(byte &value) {
    if (mBuff->getStoredDataSize() == 0) {
        return NoContent;
    }

    int end = mBuff->getEndIndex();

    if (mCursor == end && mMark != Idle) {
        mMark = Complete;
        return NoContent;
    }

    mMark = Partial;
    value = mBuff->at(mCursor);
    mCursor++;

    if (mCursor == mBuff->getCapacity()) {
        mCursor = 0;
    }

    return Continue;
}

void _ByteRingArrayReader::setCursor(int c) { 
    mCursor = c; 
}

int _ByteRingArrayReader::getCursor() { 
    return mCursor; 
}

int _ByteRingArrayReader::move(int length) {
    if (length > mBuff->getStoredDataSize()) {
        Trigger(ArrayIndexOutOfBoundsException, "length is too large");
    }

    mCursor += length;
    if (mCursor >= mBuff->getCapacity()) {
        mCursor = (mCursor - mBuff->getCapacity());
    }
    mMark = Partial;
    
    return mCursor;
}

int _ByteRingArrayReader::getReadableLength() {
    if (mBuff->getStoredDataSize() == 0 || mMark == Complete) {
        return 0;
    }

    int end = mBuff->getEndIndex();
    if (mCursor > end) {
        //return mBuff->getStoredDataSize() - (mCursor - end);
        return mBuff->getCapacity() - mCursor + end;
    } else if(mCursor == end && mMark == Idle){
        return mBuff->getCapacity();
    } else {
        return end - mCursor;
    }
}

// bool _ByteRingArrayReader::isDrained() {
//     return mMark != Partial;
// }

void _ByteRingArrayReader::reset() {
    mBuff->reset();
    mCursor = mBuff->getStartIndex();
    mMark = Idle;
}

} // namespace obotcha
