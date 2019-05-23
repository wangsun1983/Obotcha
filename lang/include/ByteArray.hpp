#ifndef __BYTE_ARRAY_HPP__
#define __BYTE_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

#define byte char

DECLARE_SIMPLE_CLASS(ByteArray)
{
public:
    _ByteArray(int length);

    _ByteArray(byte *data,int len);

    _ByteArray(sp<_ByteArray>);

    _ByteArray(String);

    template<typename T>
    _ByteArray(T *t);

    ~_ByteArray();

    byte *toValue();

    int size();

    void clear();

    bool resize(int size);

    bool isEmpty();

    byte at(int);

    bool fill(byte v);

    bool fill(int index,byte v);

    bool fill(int index,int length,byte v);

private:
    byte *buff;

    int _size;
};

template<typename T>
_ByteArray::_ByteArray(T *t) {
    int size = sizeof(T);
    buff = (byte *)malloc(size);
    if(t == nullptr) {
        return;
    }
    
    memcpy(buff,t,size);
    _size = size;
}

}
#endif
