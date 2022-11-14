#ifndef __OBOTCHA_BYTE_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_ARRAY_READER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Definations.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayReader) {

public:
    _ByteArrayReader(ByteArray,int mod = LittleEndian);

    template <typename T>
    T read() {
        T value = 0;
        switch(mMode) {
            case BigEndian:
                _readBigEndian(value);
            break;

            case LittleEndian:
                _readLittleEndian(value);
            break;
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
        int end = std::min((int)sizeof(T) - 1,mSize - mIndex - 1);
        int next = end + 1;
        while(end >= 0) {
            value |= (((T)(mDataP[mIndex + end]&0xff))<<(8*end));
            end--;
        }

        mIndex += next;
    }

    template<typename T>
    void _readBigEndian(T &value) {
        int count = std::min((int)sizeof(T),mSize - mIndex);
        for(;count > 0;count--,mIndex++) {
            value = ((T)(value<<8)|mDataP[mIndex]);
        }
    }

    ByteArray mData;
    byte *mDataP;
    int mIndex;
    int mResult;
    int mSize;
    int mMode;
};

}
#endif
