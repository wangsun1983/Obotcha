#ifndef __OBOTCHA_BYTE_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_ARRAY_READER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"
#include "Definations.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayReader) {

public:
    _ByteArrayReader(ByteArray,int mod = LittleEndian);
    int readShort();
    int readByte();
    int readInt();
    long readLong();
    uint32_t readUint32();
    uint16_t readUint16();
    String readLine();
    int readByteArray(ByteArray);
    int getIndex();
    int getRemainSize();
    void setIndex(int);

    bool isReadable();
#if 0    
    int appendWithAdjustment(ByteArray);
#endif
    
private:
    template<typename T>
    void _read(T &value) {
        switch(mode) {
            case Global::BigEndian:
            _readBigEndian(value);
            break;

            case Global::LittleEndian:
            _readLittleEndian(value);
            break;
        }
    }

    template<typename T>
    void _readLittleEndian(T &value) {
        int count = sizeof(T)-1;
        while(count >= 0) {
            if((mIndex + count) > mSize) {
                count--;
                continue;
            }
            value |= (((T)(mDataP[mIndex + count]&0xff))<<(8*count));
            count--;
        }

        mIndex += sizeof(T);
    }

    template<typename T>
    void _readBigEndian(T &value) {
        int count = sizeof(T);
        while(count > 0) {
            if(mIndex >= mSize) {
                break;
            }

            value = ((T)(value<<8)|mDataP[mIndex]);
            count--;
            mIndex++;
        }
    }

    ByteArray mData;
    byte *mDataP;
    int mIndex;
    int mResult;
    int mSize;
    int mode;
};

}
#endif