#ifndef __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__

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

    void reset();
    
private:
    enum ReadMark {
        Idle,
        Partial,
        Complete
    };

    ByteRingArray mBuff;

    int mMark;

    int mCursor;
};

}
#endif