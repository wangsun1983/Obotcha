#ifndef __OBOTCHA_BYTE_ARRAY_HPP__
#define __OBOTCHA_BYTE_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>
#include <functional>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(ByteArray) {
public:
    explicit _ByteArray(int length,bool isSafe = false);

    explicit _ByteArray(const byte *data,uint32_t len,bool isSafe = false);

    explicit _ByteArray(const sp<_ByteArray>&,bool isSafe = false);

    explicit _ByteArray(const String &,bool isSafe = false);

    ~_ByteArray();

    byte *toValue();

    int size();

    void clear();

    byte & operator[](int i);

    int growTo(int size);

    int growBy(int size);

    int quickShrink(int size);
    int quickRestore();

    bool isEmpty();

    byte at(int);

    int fill(byte v);

    int fill(int index,byte v);

    int fill(int index,int length,byte v);

    int append(const sp<_ByteArray>&);

    int append(const sp<_ByteArray>&,int len);

    int append(byte *data,int len);

    //add foreach lambda
    using foreachCallback = std::function<int(byte &)>;
    inline void foreach(foreachCallback callback) {
        for(int i = 0;i < mSize;i++) {
            if(callback(buff[i]) < 0) {
                break;
            }
        }
    }

    String toString();

    void dump(const char *);

    void dump(const String &);

    void dumpToFile(const char *);

    void dumpToFile(const String&);

private:
    byte *buff;

    int mSize;

    bool isSafe;

    int mOriginalSize;
};

}
#endif

