#ifndef __OBOTCHA_INTEGER_HPP__
#define __OBOTCHA_INTEGER_HPP__

#include <stdio.h>
#include <sstream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Integer) IMPLEMENTS(Number)<int>{
public:
    _Integer(int v):_Number(v){}

    _Integer(Integer &v):_Number(v->toValue()){}

    static const int MAX_VALUE = 0x7fffffff;

    static const int MIN_VALUE = 0x80000000;

};

}
#endif
