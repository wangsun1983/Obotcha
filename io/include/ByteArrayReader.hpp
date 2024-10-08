#ifndef __OBOTCHA_BYTE_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_ARRAY_READER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "IO.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayReader) {
public:
    _ByteArrayReader(ByteArray,st(IO)::Endianness mod = st(IO)::Endianness::Little);

    template <typename T>
    T read() {
        Panic(getRemainSize() == 0,
                ArrayIndexOutOfBoundsException,"no remain data")

        T value = 0;
        if(mMode == st(IO)::Endianness::Big) {
            _readBigEndian(value);
        } else if(mMode == st(IO)::Endianness::Little) {
            _readLittleEndian(value);
        }
        return value;
    }

    size_t read(ByteArray);
    uint64_t getIndex();
    uint64_t getRemainSize();
    void setIndex(uint64_t);
    bool isReadable();

private:
    template<typename T>
    void _readLittleEndian(T &value) {
        auto size = std::min(sizeof(T),mSize - mIndex);
        auto valuePtr = (byte*)&value;
        for(int i = 0;i < size;i++) {
            valuePtr[i] = mDataPtr[mIndex];
            mIndex++;
        }
    }

    template<typename T>
    void _readBigEndian(T &value) {
        auto size = std::min(sizeof(T),mSize - mIndex);
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
