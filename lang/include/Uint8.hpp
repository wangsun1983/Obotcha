#ifndef __OBOTCHA_UINT8_HPP__
#define __OBOTCHA_UINT8_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Uint8) IMPLEMENTS(Number)<uint8_t>{
public:
    _Uint8(uint8_t v):_Number(v){}

    _Uint8(Uint8 &v):_Number(v->toValue()) {}

};

}
#endif
