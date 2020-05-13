#ifndef __OBOTCHA_BYTE_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_ARRAY_READER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum ByteArrayReaderResult {
   ByteArrayReadSuccess = 0,
   ByteArrayReadFail,
};

DECLARE_SIMPLE_CLASS(ByteArrayReader) {

public:
    _ByteArrayReader(ByteArray);
    int readShort();
    int readByte();
    int readInt();
    long readLong();
    String readLine();
    int readByteArray(ByteArray);
    int getIndex();
    int getRemainSize();
    void setIndex(int);
    int appendWithAdjustment(ByteArray);

private:
    ByteArray mData;
    byte *mDataP;
    int mIndex;
    int mResult;
    int mSize;
};

}
#endif