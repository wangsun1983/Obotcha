#ifndef __OBOTCHA_UINT64_HPP__
#define __OBOTCHA_UINT64_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Uint64) IMPLEMENTS(Number)<uint64_t> {
public:
    _Uint64(uint64_t v):_Number(v){}

    _Uint64(Uint64 &v):_Number(v->toValue()) {}

    static const uint64_t MaxValue = 0xFFFFFFFFFFFFFFFF;

    static const uint64_t MinValue = 0x0;
};

}
#endif
