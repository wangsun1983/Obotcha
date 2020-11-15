#ifndef __OBOTCHA_BYTE_HPP__
#define __OBOTCHA_BYTE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"
#include <cstddef>

namespace obotcha {

class _String;

#define byte unsigned char

DECLARE_SIMPLE_CLASS(Byte) IMPLEMENTS(Number)<byte>{
public:
    _Byte(byte v):_Number(v){}

    _Byte(Byte &v):_Number(v->toValue()) {}
};

}
#endif