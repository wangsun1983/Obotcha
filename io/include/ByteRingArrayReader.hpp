#ifndef __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__
#define __OBOTCHA_BYTE_RING_ARRAY_READER_HPP__

#include <vector>

#include "Object.hpp"
#include "ByteRingArray.hpp"
#include "Byte.hpp"
#include "Definations.hpp"

namespace obotcha {

DECLARE_CLASS(ByteRingArrayReader) {

public:
    _ByteRingArrayReader(ByteRingArray,int mod = Defination::LittleEndian);
    ByteArray pop();
    int readNext(byte &);

    template <typename T>
    int read(T &val) {
        std::vector<byte> vec;
        byte v = 0;
        if (mBuff->getStoredDataSize() < sizeof(T)) {
            return Defination::NoContentRead;
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

        return Defination::ContinueRead;
    }

    void setCursor(int);
    int getCursor() const;
    int move(int);
    int getReadableLength() const;
    void reset();

private:
    template<typename T>
    T _readLittleEndian(std::vector<byte> v) {
        size_t count = v.size() - 1;
        T value = 0;
        while(count >= 0) {
          value |= (((T)(v[count]&0xff))<<(8*count));
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