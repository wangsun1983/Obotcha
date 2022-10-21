#ifndef __OBOTCHA_BYTE_ARRAY_WRITER_HPP__
#define __OBOTCHA_BYTE_ARRAY_WRITER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayWriter) {

  public:
    _ByteArrayWriter(int mode = LittleEndian);
    _ByteArrayWriter(ByteArray, int mode = LittleEndian);

    template <typename T>
    int write(T value) {
        if (!writeSizeCheck(sizeof(T))) {
            return -1;
        }
        switch (mode) {
            case Global::BigEndian:
                _writeBigEndian(value);
                break;

            case Global::LittleEndian:
                _writeLittleEndian(value);
                break;
        }

        return 0;
    }

    template <typename T = ByteArray>
    int write(ByteArray data) {
        if (!writeSizeCheck(data->size())) {
            return -1;
        }

        memcpy(&mDataP[mIndex], data->toValue(), data->size());
        mIndex += data->size();

        return 0;
    }

    int write(ByteArray, int start,int length);
    int write(byte *, int);

    template<typename T = String>
    int write(String str) {
        return write(str->toChars(),str->size());
    }


    int write(const char *str,int size = -1) {
        if(size == -1) {
            size = strlen(str);
        }

        if (!writeSizeCheck(size)) {
            return -1;
        }

        memcpy(&mDataP[mIndex], str, size);
        mIndex += size;
        return 0;
    }

    void skipBy(int length);
    int getIndex();
    void setIndex(int);

    void updateSize();
    void reset();

    int getReminderSize();

    ByteArray getByteArray();

  private:
    ByteArray mData;
    byte *mDataP;
    int mIndex;
    int mSize;
    int mType;
    int mode;

    static const int DefaultDataSize;
    enum ByteArrayWriteType { Dynamic = 0, Static };

    bool writeSizeCheck(int size);

    template <typename T> void _writeLittleEndian(T  value) {
        int count = 0;
        while (count < sizeof(T)) {
            mDataP[mIndex] = (value >> (count * 8) & 0xff);
            count++;
            mIndex++;
        }
    }

    template <typename T> void _writeBigEndian(T  value) {
        int count = sizeof(T) - 1;
        while (count >= 0) {
            mDataP[mIndex] = (value >> (count * 8) & 0xff);
            count--;
            mIndex++;
        }
    }
};

} // namespace obotcha
#endif
