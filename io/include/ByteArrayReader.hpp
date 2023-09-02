#ifndef __OBOTCHA_BYTE_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_ARRAY_READER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "IO.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayReader) {
public:
    _ByteArrayReader(ByteArray,st(IO)::Endianness mod = st(IO)::Endianness::Little);

    template <typename T>
    T read() {
        T value = 0;
        if(mMode == st(IO)::Endianness::Big) {
            _readBigEndian(value);
        } else if(mMode == st(IO)::Endianness::Little) {
            _readLittleEndian(value);
        }
        return value;
    }

    int read(ByteArray);
    uint64_t getIndex();
    uint64_t getRemainSize();
    void setIndex(uint64_t);
    bool isReadable();

private:
    template<typename T>
    void _readLittleEndian(T &value) {
        int size = std::min(sizeof(T),mSize - mIndex);
        memcpy((byte *)&value,mDataPtr + mIndex,size);
        mIndex += size;
    }

    template<typename T>
    void _readBigEndian(T &value) {
        int size = std::min(sizeof(T),mSize - mIndex);
        auto valuePtr = (byte*)&value;
        for(int i = 0;i < size;i++) {
            valuePtr[size - i - 1] = mDataPtr[mIndex];
            mIndex++;
        }
    }

    ByteArray mData;
    byte *mDataPtr;
    uint64_t mIndex = 0;
    uint64_t mSize;
    st(IO)::Endianness mMode;
};

}
#endif
