#ifndef __OBOTCHA_BYTE_ARRAY_WRITER_HPP__
#define __OBOTCHA_BYTE_ARRAY_WRITER_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Inspect.hpp"
#include "String.hpp"
#include "Definations.hpp"
#include "IllegalStateException.hpp"

namespace obotcha {

DECLARE_CLASS(ByteArrayWriter) {

  public:
    explicit _ByteArrayWriter(int mode = Defination::LittleEndian);
    _ByteArrayWriter(ByteArray, int mode = Defination::LittleEndian);

    template <typename T>
    int write(T value) {
        Inspect(!preCheck(sizeof(T)),-1)
        switch (mMode) {
            case Defination::BigEndian:
                _writeBigEndian(value);
                break;

            case Defination::LittleEndian:
                _writeLittleEndian(value);
                break;
            
            default:
                Trigger(IllegalStateException,"unknown mode")
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
    int getIndex();
    void setIndex(int);
    void reset();
    int getReminderSize();
    ByteArray getByteArray();

  private:
    ByteArray mData;
    byte *mDataPtr;
    int mIndex;
    int mSize;
    int mType;
    int mMode;

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
        uint8_t * valuePtr = (uint8_t *)&value;
        for(int count = sizeof(T) - 1;count >= 0;count--,mIndex++) {
            mDataPtr[mIndex] = valuePtr[count];
        }
    }
};

} // namespace obotcha
#endif
