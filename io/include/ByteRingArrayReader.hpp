#ifndef __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__

#include <vector>

#include "Object.hpp"
#include "ByteRingArray.hpp"
#include "Byte.hpp"

namespace obotcha {

DECLARE_CLASS(ByteRingArrayReader) {

public:
    enum ByteRingArrayReadStatus { Continue = 0, NoContent };

    _ByteRingArrayReader(ByteRingArray,int mod = LittleEndian);

    ByteArray pop();

    int readNext(byte &);

    template <typename T>
    int read(T &val) {
        std::vector<byte> vec;
        byte v = 0;
        if (mBuff->getAvailDataSize() < sizeof(T)) {
            return NoContent;
        }
        
        for(int i = sizeof(T);i>0;i--) {
            readNext(v);
            vec.push_back(v);
        }
        switch(mMode) {
            case LittleEndian:
            val = _readLittleEndian<T>(vec);
            break;

            case BigEndian:
            val = _readBigEndian<T>(vec);
            break;
        }

        return Continue;
    }

    void setCursor(int);

    int getCursor();

    int move(int);

    int getReadableLength();

    void reset();

    bool isDrained();

private:
    template<typename T>
    T _readLittleEndian(std::vector<byte> v) {
        int count = v.size() - 1;
        T value = 0;
        while(count >= 0) {
          value |= (((T)(v[count]&0xff))<<(8*count));
          count--;
        }

        return value;
    }

    template<typename T>
    T _readBigEndian(std::vector<byte> v) {
        int size = v.size();
        int count = 0;
        T value = 0;
        while(count < size) {
          value = ((T)(value<<8)|v[count]);
          count++;
        }

        return value;
    }

    enum ReadMark { 
      Idle = 0, 
      Partial, 
      Complete 
    };

    ByteRingArray mBuff;

    int mMark;

    int mCursor;

    int mMode;
};

} // namespace obotcha
#endif