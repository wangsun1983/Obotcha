#ifndef __OBOTCHA_BYTE_ARRAY_HPP__
#define __OBOTCHA_BYTE_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>
#include <functional>

#include "Object.hpp"
#include "Byte.hpp"

namespace obotcha {
class _String;

DECLARE_CLASS(ByteArray) {
public:
    explicit _ByteArray(int length,bool isSafe = false);

    explicit _ByteArray(const byte *data,uint32_t len,bool isSafe = false);

    explicit _ByteArray(const sp<_ByteArray>&,bool isSafe = false);

    explicit _ByteArray(const sp<_String> str,bool isSafe = false);

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

    int fill(int start,int length,byte v);

    int append(const sp<_ByteArray>&);

    int append(const sp<_ByteArray>&,int len);

    int append(byte *data,int len);

    template<typename U>
    U *get() {
        return (U*)buff;
    }

    template<typename U>
    int apply(U *p) {
        if(mSize < sizeof(U)) {
            return -1;
        }

        memcpy(buff,p,sizeof(U));
        return 0;
    }

    //add foreach lambda
    using foreachCallback = std::function<int(byte &)>;
    inline void foreach(foreachCallback callback) {
        for(int i = 0;i < mSize;i++) {
            if(callback(buff[i]) == Global::Break) {
                break;
            }
        }
    }

    sp<_String> toString();

    void dump(const char *tag);

    void dump(const sp<_String> &tag);

    void dumpToFile(const char *path);

    void dumpToFile(const sp<_String>& path);

private:
    byte *buff;

    int mSize;

    bool isSafe;

    int mOriginalSize;
};

}
#endif

