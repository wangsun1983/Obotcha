#ifndef __BYTE_RING_ARRAY_HPP__
#define __BYTE_RING_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ByteRingArray) {
public:
   _ByteRingArray(int size);

   void push(ByteArray);

   ByteArray pop(int size);

   int getAvailDataSize();

   ByteArray popAll();

   byte at(int m);
   
private:
    byte *mBuff;

    int mStart;

    int mEnd;

    int mSize;
};

}
#endif

