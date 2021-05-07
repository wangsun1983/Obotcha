#ifndef __OBOTCHA_BYTE_RING_ARRAY_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ByteRingArray) {
public:
    enum ByteRingArrayStatus {
        ByteRingArrayFull = 0,
        ByteRingArrayEmpty,
        ByteRingArrayPartial
    };

    _ByteRingArray(int size);

    ~_ByteRingArray();

    bool push(byte b);

    byte pop();

    bool push(const ByteArray &);

    bool push(const ByteArray &,int start,int length);

    bool push(byte *,int,int);

    ByteArray pop(int size);

    ByteArray popByEnd(int);

    int getAvailDataSize();

    int getSize();

    int getStartIndex();

    int getEndIndex();

    ByteArray popAll();

    byte at(int m);

    int getStatus();

    using foreachCallback = std::function<int(byte &)>;
    inline void foreach(foreachCallback callback) {
        int cursor = mStart;
        while(cursor != mEnd) {
            if(callback(mBuff[cursor]) < 0) {
                break;
            }

            cursor++;
            if(cursor == mSize) {
                cursor = 0;
            }
        }
    }

    //just for test
    void setStartIndex(int);
    void setEndIndex(int);
    void setStatus(int);

    void reset();
   
private:

    byte *mBuff;

    int mStart;

    int mEnd;

    int mSize;

    int mStatus;

    
};

}
#endif

