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
   
   bool push(ByteArray);

   bool push(ByteArray,int start,int length);

   ByteArray pop(int size);

   ByteArray popByEnd(int);

   int getAvailDataSize();

   int getSize();

   int getStartIndex();

   int getEndIndex();

   ByteArray popAll();

   byte at(int m);

   int getStatus();
   
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

