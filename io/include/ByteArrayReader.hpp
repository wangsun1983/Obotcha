#ifndef __OBOTCHA_BYTE_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_ARRAY_READER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Definations.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayReader) {
public:
    _ByteArrayReader(ByteArray,int mod = st(Defination)::LittleEndian);

    template <typename T>
    T read() {
        T value = 0;
        if(mMode == st(Defination)::BigEndian) {
            _readBigEndian(value);
        } else if(mMode == st(Defination)::LittleEndian) {
            _readLittleEndian(value);
        }
        return value;
    }

    int read(ByteArray);
    int getIndex();
    int getRemainSize();
    void setIndex(int);
    bool isReadable();

private:
    template<typename T>
    void _readLittleEndian(T &value) {
        int size = std::min((int)sizeof(T),mSize - mIndex);
        memcpy((byte *)&value,mDataPtr + mIndex,size);
        mIndex += size;
    }

    template<typename T>
    void _readBigEndian(T &value) {
        int size = std::min((int)sizeof(T),mSize - mIndex);
        byte *valuePtr = (byte*)&value;
        for(int i = 0;i < size;i++) {
            valuePtr[size - i - 1] = mDataPtr[mIndex];
            mIndex++;
        }
    }

    ByteArray mData;
    byte *mDataPtr;
    int mIndex;
    //int mResult;
    int mSize;
    int mMode;
};

}
#endif
