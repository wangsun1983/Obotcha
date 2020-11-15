#ifndef __OBOTCHA_UINT16_HPP__
#define __OBOTCHA_UINT16_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Uint16) IMPLEMENTS(Number)<uint16_t>{
public:
    _Uint16(uint16_t v):_Number(v){}

    _Uint16(Uint16 &v):_Number(v->toValue()) {}
};

}
#endif
