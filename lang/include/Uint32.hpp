#ifndef __OBOTCHA_UINT32_HPP__
#define __OBOTCHA_UINT32_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Uint32) IMPLEMENTS(Number)<uint32_t> {
public:
    _Uint32(uint32_t v):_Number(v){}

    _Uint32(Uint32 &v):_Number(v->toValue()) {}

    static const uint32_t MaxValue = 0xFFFFFFFF;

    static const uint32_t MinValue = 0x0;
};

}
#endif
