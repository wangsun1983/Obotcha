#ifndef __BYTE_ARRAY_HPP__
#define __BYTE_ARRAY_HPP__

#include <stdlib.h>
#include <memory.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

namespace obotcha {

#define byte char

enum ByteArrayExecuteResult {
    ByteArrayNoMemory = 200,
    ByteArrayWrongParam,
};

DECLARE_SIMPLE_CLASS(ByteArray)
{
public:
    _ByteArray(int length);

    _ByteArray(const byte *data,int len);

    _ByteArray(sp<_ByteArray>);

    _ByteArray(String);

    template<typename T>
    _ByteArray(T *t);

    ~_ByteArray();

    byte *toValue();

    int size();

    void clear();

    int resize(int size);

    bool isEmpty();

    byte at(int);

    int fill(byte v);

    int fill(int index,byte v);

    int fill(int index,int length,byte v);

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
