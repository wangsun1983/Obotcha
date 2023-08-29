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
        std::vector<byte> vec;
        byte v = 0;
        if (mBuff->getStoredDataSize() < sizeof(T)) {
            return st(IO)::Reader::Result::NoContent;
        }
        
        for(int i = sizeof(T);i>0;i--) {
            readNext(v);
            vec.push_back(v);
        }
        switch(mEndianness) {
            case st(IO)::Endianness::Little:
            val = _readLittleEndian<T>(vec);
            break;

            case st(IO)::Endianness::Big:
            val = _readBigEndian<T>(vec);
            break;
        }

        return st(IO)::Reader::Result::HasContent;;
    }

    void setCursor(int);
    int getCursor() const;
    int move(int);
    int getReadableLength() const;
    void reset();

private:
    enum class Mark { 
        Idle = 0, 
        Partial, 
        Complete 
    };

    template<typename T>
    T _readLittleEndian(std::vector<byte> v) {
        size_t count = v.size();
        T value = 0;
        while(count != 0) {
          value |= (((T)(v[count - 1]&0xff))<<(8*(count - 1)));
          count--;
        }

        return value;
    }

    template<typename T>
    T _readBigEndian(std::vector<byte> v) {
        size_t size = v.size();
        size_t count = 0;
        T value = 0;
        while(count < size) {
          value = ((T)(value<<8)|v[count]);
          count++;
        }

        return value;
    }

    ByteRingArray mBuff;
    Mark mMark = Mark::Idle;
    int mCursor;
    st(IO)::Endianness mEndianness;
};

} // namespace obotcha
#endif