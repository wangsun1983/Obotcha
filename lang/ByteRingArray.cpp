#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ByteRingArray.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_ByteRingArray::_ByteRingArray(int size) {
    if(size <= 0) {
        Trigger(InitializeException,"size is illeagle");
    }
    
    mSize = size;
    mBuff = (byte *)malloc(size);

    if(mBuff == nullptr) {
        Trigger(InitializeException,"alloc fail");
    }

    mStatus = Empty;
    mStart = 0;
    mEnd = 0;
}

void _ByteRingArray::reset() {
    mStatus = Empty;
    mStart = 0;
    mEnd = 0;
}

_ByteRingArray::~_ByteRingArray() {
    if(mBuff != nullptr) {
        free(mBuff);
        mBuff = nullptr;
    }
}

bool _ByteRingArray::push(byte b) {
    if(mStatus == Full) {
        Trigger(ArrayIndexOutOfBoundsException,"Ring Array push full Array!!!");
    }

    mBuff[mEnd] = b;
    if(mEnd == (mSize - 1)) {
        mEnd = 0;
    } else {
        mEnd++;
    }

    if(mEnd == mStart) {
        mStatus = Full;
    } else {
        mStatus = Partial;
    }

    return true;
}

byte _ByteRingArray::pop() {
    if(mStatus == Empty) {
        Trigger(ArrayIndexOutOfBoundsException,"Ring Array Pop Empty Array!!!");
    }

    byte c = mBuff[mStart];

    mStart++;
    
    if(mStart == mSize) {
        mStart = 0;
    } 

    if(mStart == mEnd) {
        mStatus = Empty;
    } else {
        mStatus = Partial;
    }

    return c;
}

bool _ByteRingArray::push(const ByteArray &data) {
    if(data == nullptr) {
        Trigger(IllegalArgumentException,"pop data is nullptr");
    }
    return push(data,0,data->size());  
}

bool _ByteRingArray::push(const ByteArray &array,int start,int length) {
    return push(array->toValue(),start,length);
}

bool _ByteRingArray::push(byte *array,int start,int length) {
    if(mStatus == Full ||(mSize - getAvailDataSize()) < length ) {
        Trigger(ArrayIndexOutOfBoundsException,"Ring Array Push Overflow!!!");
    }
    
    if(mEnd < mStart) {
        memcpy(mBuff + mEnd,&array[start],length);
        mEnd += length;
    } else {
        if(mEnd + length < mSize) {
            memcpy(mBuff + mEnd,&array[start],length);
            mEnd += length;
        } else {
            int len = mSize - mEnd;
            memcpy(mBuff + mEnd,&array[start],len);
            memcpy(mBuff,&array[start + len],length - len);
            mEnd = (length - len);
        }
    }
    if(mEnd == mStart) {
        mStatus = Full;
    } else {
        mStatus = Partial;
    }
    return true;
}

ByteArray _ByteRingArray::pop(int size) {
    if(size <= 0) {
        Trigger(IllegalArgumentException,"pop size is illegal");
    }

    if(mStatus == Empty) {
        Trigger(ArrayIndexOutOfBoundsException,"Ring Array Pop Empty Array!!!");
    }

    ByteArray buff = createByteArray(size);
    if(mStart >= mEnd) {
        if( mSize - (mStart - mEnd) < size) {
            Trigger(ArrayIndexOutOfBoundsException,"Ring Array Pop OverStack!!!");
        }
        
        if((mStart + size) < mSize) {
            memcpy(buff->toValue(),mBuff + mStart,size);
            mStart += size;
        } else {
            int length = mSize - mStart;
            memcpy(buff->toValue(),mBuff + mStart,length);
            memcpy(buff->toValue() + length,mBuff,size - length);
            mStart = (size - length);
        }
    } else {
        if((mEnd -mStart) < size) {
            Trigger(ArrayIndexOutOfBoundsException,"Ring Array Pop OverStack!!!");
        }
        
        memcpy(buff->toValue(),mBuff+mStart,size);
        mStart += size;
    }

    if(mStart == mEnd) {
        mStatus = Empty;
    } else {
        mStatus = Partial;
    }

    return buff;
}

int _ByteRingArray::getAvailDataSize() {
    if(mStatus == Empty) {
        return 0;
    }

    if(mStart >= mEnd) {
        return mSize-(mStart - mEnd);
    } else {
        return mEnd - mStart;
    }
}

int _ByteRingArray::getSize() {
    return mSize;
}

int _ByteRingArray::getStartIndex() {
    return mStart;
}

int _ByteRingArray::getEndIndex() {
    return mEnd;
}

byte _ByteRingArray::at(int m) {
    
    return mBuff[m];
}

ByteArray _ByteRingArray::popAll() {
    int size = getAvailDataSize();
    return pop(size);
}

//for ByteRingArray
ByteArray _ByteRingArray::popByEnd(int end) {
    if(mStatus == Empty) {
        Trigger(ArrayIndexOutOfBoundsException,"Ring Array popAtCursor OverStack!!!");
    }
    int length = 0;
    if(mStart > end) {
        length = mSize - (mStart - end);
    } else {
        length = end - mStart;
    }
    if(length == 0) {
        return nullptr;
    }

    return pop(length);
}

int _ByteRingArray::getStatus() {
    return mStatus;
}

//just for test
void _ByteRingArray::setStartIndex(int index) {
    mStart = index;
}

void _ByteRingArray::setEndIndex(int index) {
    mEnd = index;
}

void _ByteRingArray::setStatus(int status) {
    this->mStatus = status;
}

}


