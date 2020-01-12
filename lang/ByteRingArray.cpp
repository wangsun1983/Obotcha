#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ByteRingArray.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

_ByteRingArray::_ByteRingArray(int size) {
    mSize = size;
    mBuff = (byte *)malloc(size);
}

void _ByteRingArray::push(ByteArray data) {
    if((mSize - abs(mStart - mEnd)) < data->size()) {
        throw createArrayIndexOutOfBoundsException("Ring Array Push OverStack!!!");
    }

    if(mEnd < mStart) {
        memcpy(mBuff + mEnd,data->toValue(),data->size());
        mEnd += data->size();
    } else {
        if(mEnd + data->size() < mSize) {
            memcpy(mBuff + mEnd,data->toValue(),data->size());
            mEnd += data->size();
        } else {
            int length = mSize - mEnd;
            memcpy(mBuff + mEnd,data->toValue(),length);
            memcpy(mBuff,data->toValue() + length,data->size() - length);
            mEnd = data->size() - length;
        }
    }
}

ByteArray _ByteRingArray::pop(int size) {
    if(mEnd == mStart) {
        throw createArrayIndexOutOfBoundsException("Ring Array Pop OverStack!!!");
    }

    if(mStart > mEnd) {
        if((mStart - mEnd) < size) {
            throw createArrayIndexOutOfBoundsException("Ring Array Pop OverStack!!!");
        }
        
        ByteArray buff = createByteArray(size);
        if((mStart + size) < mSize) {            
            memcpy(buff->toValue(),mBuff + mStart,size);
            mStart += size;
        } else {
            int length = mSize - mStart;
            memcpy(buff->toValue(),mBuff + mStart,length);
            memcpy(buff->toValue() + length,mBuff,size - length);
            mStart += (size - length);
        }

        return buff;
    } else if(mEnd > mStart) {
        if((mSize - (mStart - mEnd) < size)) {
            throw createArrayIndexOutOfBoundsException("Ring Array Pop OverStack!!!");
        }
        ByteArray buff = createByteArray(size);
        memcpy(buff->toValue(),mBuff+mStart,size);
        mStart += size;
        return buff;
    }

    return nullptr;
}

int _ByteRingArray::getAvailDataSize() {
    if(mStart > mEnd) {
        return mSize - abs(mStart - mEnd);
    } else {
        return mEnd - mStart;
    }
}

byte _ByteRingArray::at(int m) {
    return mBuff[m];
}

ByteArray _ByteRingArray::popAll() {
    //TODO
    mStart = 0;
    mEnd = 0;
    return nullptr;
}

}


