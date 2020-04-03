#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <stdio.h>
#include <sstream>

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Integer) {
public:
    _Integer(int v);

    _Integer(Integer &v);

    int toValue();

    bool equals(Integer &p);

    bool equals(int p);

    bool equals(const _Integer *p);

    void update(int v);

    void update(sp<_Integer> v);

    sp<_String> toHexString();

    static sp<_String> toHexString(int i);

    sp<_String> toOctalString();

    static sp<_String> toOctalString(int i);

    sp<_String> toBinaryString();

    static sp<_String> toBinaryString(int i);

    sp<_String> toString();

    static sp<_String> toString(int i);

    static int parseDecInt(sp<_String>);

    static int parseHexInt(sp<_String>);

    static int parseOctInt(sp<_String>);

    static int parseBinaryInt(sp<_String>);

    ~_Integer();

    static const int MAX_VALUE = 0x7fffffff;

    static const int MIN_VALUE = 0x80000000;

private:
    static void binaryRecursion(int n,std::stringstream &ss);

    int val;
};

}
#endif
