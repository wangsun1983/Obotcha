#ifndef __OBOTCHA_BYTE_ARRAY_HPP__
#define __OBOTCHA_BYTE_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>

#include "String.hpp"
#include "ListObject.hpp"
#include "ListPointer.hpp"

namespace obotcha {

DECLARE_BYTE_ARRAY(ByteArray) {
public:
    _ByteArray(int length);

    _ByteArray(const byte *data,uint32_t len);

    _ByteArray(sp<_ByteArray>);

    _ByteArray(String);

    ~_ByteArray();

    byte *toValue();

    int size();

    void clear();

    unsigned char & operator[](int i);

    int growTo(int size);

    int growBy(int size);

    void quickShrink(int size);

    bool isEmpty();

    byte at(int);

    int fill(byte v);

    int fill(int index,byte v);

    int fill(int index,int length,byte v);

    int append(sp<_ByteArray>);

    int append(sp<_ByteArray>,int len);

    int append(byte *data,int len);

    String toString();

    void dump(const char *);

    void dump(String);

    void dumpToFile(const char *);

    void dumpToFile(String);

    void setMode(int);

    static const int SafeMode;

    static const int NormalMode;

private:
    byte *buff;

    int mSize;

    int mMode;
};

}
#endif

