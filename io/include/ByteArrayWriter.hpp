#ifndef __OBOTCHA_BYTE_ARRAY_WRITER_HPP__
#define __OBOTCHA_BYTE_ARRAY_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ByteArrayWriter) {

public:
    _ByteArrayWriter(int mode = LittleEndian);
    _ByteArrayWriter(ByteArray,int mode = LittleEndian);

    int writeShort(int v);
    int writeByte(byte b);
    int writeInt(int v);
    long writeLong(long v);
    int writeByteArray(ByteArray);
    int writeByteArray(ByteArray,int);
    int writeString(String);
    int writeString(const char *);
    void skipBy(int length);
    int getIndex();

    void updateSize();
    void reset();

    int write(byte *,int);

    ByteArray getByteArray();

    enum WriteMode {
        BigEndian = 0,
        LittleEndian,
    };

private:
    ByteArray mData;
    byte *mDataP;
    int mIndex;
    int mSize;
    int mType;
    int mode;

    static const int DefaultDataSize;
    enum ByteArrayWriteType {
        Dynamic = 0,
        Static
    };
    
    bool writeSizeCheck(int size);

    template<typename T>
    void _write(T &value) {
        switch(mode) {
            case BigEndian:
            _writeBigEndian(value);
            break;

            case LittleEndian:
            _writeLittleEndian(value);
            break;
        }
    }

    template<typename T>
    void _writeLittleEndian(T &value) {
        int count = 0;
        while(count <sizeof(T)) {
            mDataP[mIndex] = (value>>(count*8)&0xff);
            count++;
            mIndex++;
        }
    }

    template<typename T>
    void _writeBigEndian(T &value) {
        int count = sizeof(T) - 1;
        while(count >= 0) {
            mDataP[mIndex] = (value>>(count*8)&0xff);
            count--;
            mIndex++;
        }
    }
};

}
#endif