#ifndef __UINT64_HPP__
#define __UINT64_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Uint64) {
public:
    _Uint64(uint64_t v);

    _Uint64(Uint64 v);

    uint64_t toValue();

    bool equals(Uint64 p);

    bool equals(uint64_t p);

    bool equals(_Uint64 *p);
/*
    Integer valueOf(String v);
*/
    ~_Uint64();

private:
    uint64_t val;
};

}
#endif
