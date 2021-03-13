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
    _Integer();
    
    _Integer(int v);

    _Integer(Integer &v);

    int toValue();

    bool equals(Integer &p);

    bool equals(int p);

    bool equals(const _Integer *p);

    void update(int v);

    void update(sp<_Integer> v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(int i);
    
    static int parseDecInt(sp<_String>);

    static int parseHexInt(sp<_String>);

    static int parseOctInt(sp<_String>);

    static int parseBinaryInt(sp<_String>);

    static sp<_String> className();
    
    uint64_t hashcode();
    
    ~_Integer();

    static const int MAX_VALUE = 0x7fffffff;

    static const int MIN_VALUE = 0x80000000;

private:
    int val;
};

}
#endif
