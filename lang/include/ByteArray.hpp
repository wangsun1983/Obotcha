#ifndef __BYTE_ARRAY_HPP__
#define __BYTE_ARRAY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

#define byte char

DECLARE_SIMPLE_CLASS(ByteArray)
{
public:
    _ByteArray(int length);

    _ByteArray(byte *data,int len);

    _ByteArray(sp<_ByteArray>);

    ~_ByteArray();

    byte *toValue();

    int size();

    void clear();

    bool resize(int size);

    bool isEmpty();

    byte at(int);

    void fill(byte v);

private:
    byte *buff;

    int _size;
};

}
#endif