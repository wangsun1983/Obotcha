#ifndef __OBOTCHA_BYTE_RING_ARRAY_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(ByteRingArray) {
public:
    enum ByteRingArrayStatus {
        Full = 0,
        Empty,
        Partial
    };

    _ByteRingArray(int size);

    _ByteRingArray(sp<_ByteRingArray>);

    ~_ByteRingArray();

    bool push(byte b);

    byte pop();

    bool push(const ByteArray &);

    bool push(const ByteArray &,int start,int length);

    bool push(byte *,int,int);

    ByteArray pop(int size);

    ByteArray popTo(int index);

    int getAvailDataSize();

    int getCapacity();

    int getStartIndex();

    int getEndIndex();

    ByteArray popAll();

    byte at(int m);

    //just for test
    void setStartIndex(int);
    void setEndIndex(int);
    int getNextIndex();
    void setNextIndex(int);
    void setSize(int);
    //void setStatus(int);

    void reset();
   
private:

    byte *mBuff;

    int mNext;
    int mCapacity;
    int mSize;
    
};

}
#endif

