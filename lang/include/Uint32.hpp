#ifndef __UINT32_HPP__
#define __UINT32_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Uint32) {
public:
    _Uint32(uint32_t v);

    _Uint32(Uint32 v);

    uint32_t toValue();

    bool equals(Uint32 p);

    bool equals(uint32_t p);

    bool equals(_Uint32 *p);
/*
    Integer valueOf(String v);
*/
    ~_Uint32();

    static const uint32_t MAX_VALUE = 0xFFFFFFFF;

    static const uint32_t MIN_VALUE = 0x0;

private:
    uint32_t val;
};

}
#endif
