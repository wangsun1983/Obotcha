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
    printf("ring buff size is %d \n",size);
    mSize = size;
    mBuff = (byte *)malloc(size);
    mStatus = ByteRingArrayEmpty;
    mStart = 0;
    mEnd = 0;
}

_ByteRingArray::~_ByteRingArray() {
    if(mBuff != nullptr) {
        free(mBuff);
        mBuff = nullptr;
    }
}

void _ByteRingArray::push(byte b) {
    if(mStatus == ByteRingArrayFull) {
        throw ArrayIndexOutOfBoundsException("Ring Array Push OverStack!!!");
    }

    mBuff[mEnd] = b;
    if(mEnd == (mSize - 1)) {
        mEnd = 0;
    } else {
        mEnd++;
    }

    if(mEnd == mStart) {
        mStatus = ByteRingArrayFull;
    } else {
        mStatus = ByteRingArrayPartial;
    }
}

byte _ByteRingArray::pop() {
    if(mStatus == ByteRingArrayEmpty) {
        throw ArrayIndexOutOfBoundsException("Ring Array Pop Empty Array!!!");
    }

    byte c = mBuff[mStart];

    mStart++;
    
    if(mStart == mSize) {
        mStart = 0;
    } 

    if(mStart == mEnd) {
        mStatus = ByteRingArrayEmpty;
    } else {
        mStatus = ByteRingArrayPartial;
    }

    return c;
}

void _ByteRingArray::push(ByteArray data) {
    push(data,0,data->size());
#if 0    
    if(mStatus == ByteRingArrayFull) {
        throw ArrayIndexOutOfBoundsException("Ring Array Push OverStack!!!");
    }

    if((mSize - abs(mStart - mEnd)) < data->size()) {
        throw ArrayIndexOutOfBoundsException("Ring Array Push OverStack!!!");
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
            mEnd = (data->size() - length);
        }
    }

    if(mEnd == mStart) {
        mStatus = ByteRingArrayFull;
    } else {
        mStatus = ByteRingArrayPartial;
    }
#endif    
}

void _ByteRingArray::push(ByteArray array,int start,int length) {
    if(mStatus == ByteRingArrayFull) {
        throw ArrayIndexOutOfBoundsException("Ring Array Push OverStack!!!");
    }

    if((mSize - abs(mStart - mEnd)) < length) {
        throw ArrayIndexOutOfBoundsException("Ring Array Push OverStack!!!");
    }
    
    if(mEnd < mStart) {
        memcpy(mBuff + mEnd,&array->toValue()[start],length);
        mEnd += length;
    } else {
        if(mEnd + length < mSize) {
            memcpy(mBuff + mEnd,&array->toValue()[start],length);
            mEnd += length;
        } else {
            int len = mSize - mEnd;
            memcpy(mBuff + mEnd,&array->toValue()[start],len);
            memcpy(mBuff,&array->toValue()[start + len],length - len);
            mEnd = (length - len);
        }
    }

    if(mEnd == mStart) {
        mStatus = ByteRingArrayFull;
    } else {
        mStatus = ByteRingArrayPartial;
    }
}

ByteArray _ByteRingArray::pop(int size) {
    if(mStatus == ByteRingArrayEmpty) {
        throw ArrayIndexOutOfBoundsException("Ring Array Pop Empty Array!!!");
    }

    ByteArray buff = createByteArray(size);
    printf("mStart is %d,mEnd is %d,size is %d \n",mStart,mEnd,mSize);
    if(mStart >= mEnd) {
        if( mSize - (mStart - mEnd) < size) {
            throw ArrayIndexOutOfBoundsException("Ring Array Pop OverStack!!!");
        }
        
        if((mStart + size) < mSize) {
            printf("pop 1 \n");          
            memcpy(buff->toValue(),mBuff + mStart,size);
            mStart += size;
        } else {
            printf("pop 2 \n");
            int length = mSize - mStart;
            memcpy(buff->toValue(),mBuff + mStart,length);
            memcpy(buff->toValue() + length,mBuff,size - length);
            mStart = (size - length);
        }
    } else if(mEnd > mStart) {
        printf("pop 3 \n");
        if((mEnd -mStart) < size) {
            throw ArrayIndexOutOfBoundsException("Ring Array Pop OverStack!!!");
        }
        
        memcpy(buff->toValue(),mBuff+mStart,size);
        mStart += size;
    }

    if(mStart == mEnd) {
        mStatus = ByteRingArrayEmpty;
    } else {
        mStatus = ByteRingArrayPartial;
    }

    return buff;
}

int _ByteRingArray::getAvailDataSize() {
    if(mStatus == ByteRingArrayEmpty) {
        return 0;
    }

    if(mStart >= mEnd) {
        return mSize - abs(mStart - mEnd);
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
    if(m >= mSize) {
        throw ArrayIndexOutOfBoundsException("Ring Array At OverStack!!!");
    }
    return mBuff[m];
}

ByteArray _ByteRingArray::popAll() {
    int size = getAvailDataSize();
    return pop(size);
}

ByteArray _ByteRingArray::popByEnd(int end) {
    if(mStatus == ByteRingArrayEmpty) {
        throw ArrayIndexOutOfBoundsException("Ring Array popAtCursor OverStack!!!");
    }
    printf("pop by end at %d \n",end);

    int length = 0;
    if(mStart >= end) {
        length = mSize - abs(mStart - end);
    } else {
        length = end - mStart;
    }

    printf("pop by end length is %d \n",length);

    return pop(length);
}

ByteRingArrayStatus _ByteRingArray::getStatus() {
    return mStatus;
}

}


