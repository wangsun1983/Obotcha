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

#include "String.hpp"
#include "ByteArray.hpp"
#include "ByteRingArrayReader.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "Error.hpp"

namespace obotcha {

_ByteRingArrayReader::_ByteRingArrayReader(ByteRingArray b) {
    mBuff = b;
    mCursor = mBuff->getStartIndex();
    mMark = Idle;
}

ByteArray _ByteRingArrayReader::pop() {
    ByteArray result = nullptr;

    try {
        if(mMark == Complete) {
            result = mBuff->popAll();
            mMark = Idle;
        } else{
            result = mBuff->popByEnd(mCursor);
        }
    } catch(ArrayIndexOutOfBoundsException &e){
    }

    return result;
}

int _ByteRingArrayReader::readNext(byte &value) {
    if(mBuff->getStatus() == st(ByteRingArray)::ByteRingArrayEmpty) {
        return ByteRingArrayReadComplete;
    }

    int start = mBuff->getStartIndex();
    int end = mBuff->getEndIndex();

    if(mCursor == end) {
        if(mMark != Idle) {
            mMark = Complete;
            return ByteRingArrayReadComplete;
        }
    }
    mMark = Partial;

    value = mBuff->at(mCursor);
    mCursor++;

    if(mCursor == mBuff->getSize()) {
        mCursor = 0;
    }

    return ByteRingArrayReadContinue;
}

void _ByteRingArrayReader::setCursor(int c) {
    mCursor = c;
}

int _ByteRingArrayReader::getCursor() {
    return mCursor;
}

int _ByteRingArrayReader::move(int length) {
    mCursor += length;
    if(mCursor > mBuff->getSize()) {
        mCursor = (mCursor - mBuff->getSize());
    }

    return mCursor;
}

int _ByteRingArrayReader::getReadableLength() {
    if(mBuff->getStatus() == st(ByteRingArray)::ByteRingArrayEmpty) {
        return 0;
    }

    int end = mBuff->getEndIndex();
    int length = mBuff->getSize();

    if( mCursor >= end) {
        return mBuff->getSize() - (mCursor - end);
    } else {
        return end - mCursor;
    }
}

void _ByteRingArrayReader::reset() {
    mBuff->reset();
    mCursor = mBuff->getStartIndex();
    mMark = Idle;
}
    

}
