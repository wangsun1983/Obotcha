#ifndef __BYTE_RING_ARRAY_HPP__
#define __BYTE_RING_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum ByteRingArrayStatus {
    ByteRingArrayFull,
    ByteRingArrayEmpty,
    ByteRingArrayPartial
};

DECLARE_SIMPLE_CLASS(ByteRingArray) {
public:
   _ByteRingArray(int size);

   ~_ByteRingArray();

   void push(byte b);

   byte pop();
   
   void push(ByteArray);

   void push(ByteArray,int start,int length);

   ByteArray pop(int size);

   ByteArray popByEnd(int);

   int getAvailDataSize();

   int getSize();

   int getStartIndex();

   int getEndIndex();

   ByteArray popAll();

   byte at(int m);

   ByteRingArrayStatus getStatus();
   
private:
    byte *mBuff;

    int mStart;

    int mEnd;

    int mSize;

    ByteRingArrayStatus mStatus;

    
};

}
#endif

