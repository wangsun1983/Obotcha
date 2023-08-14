#ifndef __OBOTCHA_BYTE_ARRAY_WRITER_HPP__
#define __OBOTCHA_BYTE_ARRAY_WRITER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Inspect.hpp"
#include "String.hpp"
#include "Definations.hpp"
#include "IllegalStateException.hpp"
#include "IO.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayWriter) {

  public:
    explicit _ByteArrayWriter(st(IO)::Endianness endiness = st(IO)::Endianness::Little);
    _ByteArrayWriter(ByteArray,st(IO)::Endianness endiness = st(IO)::Endianness::Little);

    template <typename T>
    int write(T value) {
        Inspect(!preCheck(sizeof(T)),-1)
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
    int write(ByteArray data) {
        return write(data,0,data->size());
    }

    template<typename T = String>
    int write(String str) {
        return write(str->toChars(),str->size());
    }

    int write(ByteArray, int start,int length);
    int write(byte *, int);
    int write(const char *str,int size = -1);
    void skipBy(int length);
    int getIndex() const;
    void setIndex(int);
    void reset();
    int getReminderSize() const;
    ByteArray getByteArray();

  private:
    ByteArray mData;
    byte *mDataPtr;
    int mIndex = 0;
    int mSize;
    int mType;
    st(IO)::Endianness mEndiness;

    static const int DefaultDataSize;

    enum ByteArrayWriteType {
        Dynamic = 0,
        Static
    };

    bool preCheck(int size);

    template <typename T> void _writeLittleEndian(T  value) {
        memcpy(&mDataPtr[mIndex],&value,sizeof(T));
        mIndex += sizeof(T);
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
