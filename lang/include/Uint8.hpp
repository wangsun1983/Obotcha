#ifndef __UINT8_HPP__
#define __UINT8_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Uint8) {
public:
    _Uint8(uint8_t v);

    _Uint8(Uint8 v);

    uint8_t toValue();

    bool equals(Uint8 p);

    bool equals(uint8_t p);

    bool equals(_Uint8 *p);
/*
    Integer valueOf(String v);
*/
    ~_Uint8();

    static const uint8_t MAX_VALUE = 0xFF;

    static const uint8_t MIN_VALUE = 0x0;

private:
    uint8_t val;
};

}
#endif
