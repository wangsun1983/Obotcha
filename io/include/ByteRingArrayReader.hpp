#ifndef __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__

#include <vector>

#include "Object.hpp"
#include "ByteRingArray.hpp"
#include "Byte.hpp"
#include "IO.hpp"

namespace obotcha {

DECLARE_CLASS(ByteRingArrayReader) {

public:
    _ByteRingArrayReader(ByteRingArray,st(IO)::Endianness mod = st(IO)::Endianness::Little);
    ByteArray pop();
    st(IO)::Reader::Result readNext(byte &);

    template <typename T>
    st(IO)::Reader::Result read(T &val) {
        if (mBuff->getStoredDataSize() < sizeof(T)) {
            return st(IO)::Reader::Result::NoContent;
        }

        switch(mEndianness) {
            case st(IO)::Endianness::Little:
            val = _readLittleEndian<T>();
            break;

            case st(IO)::Endianness::Big:
            val = _readBigEndian<T>();
            break;
        }

        return st(IO)::Reader::Result::HasContent;;
    }

    void setCursor(size_t);
    size_t getCursor() const;
    size_t move(size_t);
    size_t getReadableLength() const;
    void reset();

private:
    template<typename T>
    T _readLittleEndian() {
        T value = 0;
        byte v = 0;
        for(size_t i = sizeof(T);i>0;i--) {
            readNext(v);
            value |= ((T)v << 8*(sizeof(T) - i));
        }

        return value;
    }

    template<typename T>
    T _readBigEndian() {
        T value = 0;
        byte v = 0;
        for(size_t i = sizeof(T);i>0;i--) {
            readNext(v);
            value = (value << 8|v);
        }

        return value;
    }

    ByteRingArray mBuff;
    size_t mCursor;
    st(IO)::Endianness mEndianness;
};

} // namespace obotcha
#endif