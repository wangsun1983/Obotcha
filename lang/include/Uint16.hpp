#ifndef __UINT16_HPP__
#define __UINT16_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Uint16) {
public:
    _Uint16(uint16_t v);

    _Uint16(Uint16 v);

    uint16_t toValue();

    bool equals(Uint16 p);

    bool equals(uint16_t p);

    bool equals(_Uint16 *p);
/*
    Integer valueOf(String v);
*/
    ~_Uint16();

    static const uint16_t MAX_VALUE = 0xFFFF;

    static const uint16_t MIN_VALUE = 0x0;

private:
    uint16_t val;
};

}
#endif
