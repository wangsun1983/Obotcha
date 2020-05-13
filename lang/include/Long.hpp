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
    _Long(long v);

    _Long(Long &v);

    long toValue();

    bool equals(Long &p);

    bool equals(long p);

    bool equals(const _Long *p);

    void update(long v);

    void update(sp<_Long> v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(int i);
    
    static long parseDecLong(sp<_String>);

    static long parseHexLong(sp<_String>);

    static long parseOctLong(sp<_String>);

    static long parseBinaryLong(sp<_String>);

    ~_Long();

private:
    long val;
};

}
#endif
