#ifndef __LONG_HPP__
#define __LONG_HPP__

#include <stdio.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Long) {
public:
    _Long(long v);

    _Long(Long v);

    long toValue();

    bool equals(Long p);

    bool equals(long p);

    bool equals(_Long *p);
/*
    Integer valueOf(String v);
*/
    ~_Long();

private:
    long val;
};

}
#endif
