#ifndef __OBOTCHA_LONG_HPP__
#define __OBOTCHA_LONG_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Long) IMPLEMENTS(Number)<long>{
public:
    _Long(long v):_Number(v){}

    _Long(Long &v):_Number(v->toValue()){}
};

}
#endif
