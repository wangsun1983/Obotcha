#ifndef __BYTE_ARRAY_WRITER_HPP__
#define __BYTE_ARRAY_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

enum ByteArrayWriterResult {
   ByteArrayWriteSuccess = 0,
   ByteArrayWritePart,
   ByteArrayWriteFail,
};

DECLARE_SIMPLE_CLASS(ByteArrayWriter) {

public:
    _ByteArrayWriter(); //dynamic array
    _ByteArrayWriter(ByteArray);

    int writeShort(int v);
    int writeByte(byte b);
    int writeInt(int v);
    long writeLong(long v);
    int writeByteArray(ByteArray);
    int writeByteArray(ByteArray,int);
    int writeString(String);
    int getIndex();

    int write(byte *,int);

    ByteArray getByteArray();

private:
    ByteArray mData;
    byte *mDataP;
    int mIndex;
    int mSize;
    int mType;

    static const int DefaultDataSize = 1024;
    static const int Dynamic = 1;
    static const int Static = 2;
};

}
#endif