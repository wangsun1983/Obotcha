#ifndef __BYTE_ARRAY_WRITER_HPP__
#define __BYTE_ARRAY_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum ByteArrayReaderResult {
   ByteArrayWriteSuccess = 0,
   ByteArrayWritePart,
   ByteArrayWriteFail,
};

DECLARE_SIMPLE_CLASS(ByteArrayWriter) {

public:
    _ByteArrayWriter(ByteArray);
    int writeShort(int v);
    int writeByte(byte b);
    int writeInt(int v);
    long writeLong(long v);
    int writeByteArray(ByteArray);
    int getIndex();

private:
    ByteArray mData;
    byte *mDataP;
    int mIndex;
    int mSize;
};

}
#endif