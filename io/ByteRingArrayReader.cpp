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
    mStartMark = mCursor;
}

ByteArray _ByteRingArrayReader::pop() {
    ByteArray result = nullptr;
    try {
        printf("pop mCursor is %d \n",mCursor);
        result = mBuff->popByEnd(mCursor);
        mStartMark = mBuff->getStartIndex();
    } catch(ArrayIndexOutOfBoundsException e){}

    return result;
}

int _ByteRingArrayReader::readNext(byte &value) {
    if(mBuff->getStatus() == ByteRingArrayEmpty) {
        return ByteRingArrayReadComplete;
    }

    int start = mBuff->getStartIndex();
    int end = mBuff->getEndIndex();

    if(mCursor == end) {
        return ByteRingArrayReadComplete;
    }
    
    if(mStartMark != start) {
        return -InvalidStatus;
    }

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

int _ByteRingArrayReader::jump(int) {}
    

}
