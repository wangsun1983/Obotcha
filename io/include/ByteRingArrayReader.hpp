#ifndef __BYTE_RING_ARRAY_READER_HPP__
#define __BYTE_RING_ARRAY_READER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteRingArray.hpp"

namespace obotcha {

enum ByteRingArrayReadStatus {
    ByteRingArrayReadContinue = 0,
    ByteRingArrayReadComplete
};

DECLARE_SIMPLE_CLASS(ByteRingArrayReader) {

public:
    _ByteRingArrayReader(ByteRingArray);

    ByteArray pop();

    int readNext(byte &);

    void setCursor(int);

    int getCursor();

    int move(int);

    int getReadableLength();
    
private:
    ByteRingArray mBuff;

    int mStartMark;

    int mCursor;
};

}
#endif