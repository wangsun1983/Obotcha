#ifndef __OBOTCHA_BYTE_ARRAY_WRITER_HPP__
#define __OBOTCHA_BYTE_ARRAY_WRITER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Inspect.hpp"
#include "String.hpp"
#include "IllegalArgumentException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "IO.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayWriter) {

  public:
    explicit _ByteArrayWriter(st(IO)::Endianness endiness = st(IO)::Endianness::Little);
    _ByteArrayWriter(ByteArray,st(IO)::Endianness endiness = st(IO)::Endianness::Little);

    template <typename T>
    size_t write(T value) {
        Panic(!preCheck(sizeof(T)),ArrayIndexOutOfBoundsException,"write")
        switch (mEndiness) {
            case st(IO)::Endianness::Big:
                _writeBigEndian(value);
                break;

            case st(IO)::Endianness::Little:
                _writeLittleEndian(value);
                break;
        }
        return 0;
    }

    template <typename T = ByteArray>
    size_t write(ByteArray data) {
        return write(data,0,data->size());
    }

    template<typename T = String>
    size_t write(String str) {
        return write(str->toChars(),str->size());
    }

    int write(ByteArray, size_t start,size_t length);
    int write(byte *, size_t);
    int write(const char *str,size_t size = 0);
    int skipBy(size_t length);
    size_t getIndex() const;
    void setIndex(size_t);
    void reset();
    size_t getRemainSize() const;
    ByteArray getByteArray();

  private:
    enum class Type {
        Dynamic = 0,
        Regular
    };
    
    ByteArray mData;
    byte *mDataPtr;
    size_t mIndex = 0;
    size_t mSize;
    _ByteArrayWriter::Type mType;
    st(IO)::Endianness mEndiness;

    static const size_t DefaultDataSize;

    bool preCheck(size_t size);

    template <typename T> void _writeLittleEndian(T  value) {
        auto valuePtr = (const uint8_t *)&value;
        for(int count = 0;count < sizeof(T);count++,mIndex++) {
            mDataPtr[mIndex] = valuePtr[count];
        }
    }

    template <typename T> void _writeBigEndian(T  value) {
        auto valuePtr = (const uint8_t *)&value;
        for(int count = sizeof(T) - 1;count >= 0;count--,mIndex++) {
            mDataPtr[mIndex] = valuePtr[count];
        }
    }
};

} // namespace obotcha
#endif
