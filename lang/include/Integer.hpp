#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Integer) {
public:
    _Integer(int v);

    _Integer(Integer v);

    int toValue();

    bool equals(Integer p);

    bool equals(int p);
/*
    Integer valueOf(String v);
*/
    ~_Integer();

    static const int MAX_VALUE = 0x7fffffff;

    static const int MIN_VALUE = 0x80000000;
private:
    int val;
};

}
#endif
