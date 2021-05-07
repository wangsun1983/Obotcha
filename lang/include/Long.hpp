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
    _Long();
    
    _Long(long v);

    _Long(const Long &v);

    long toValue();

    bool equals(const Long &p);

    bool equals(long p);

    bool equals(const _Long *p);

    void update(long v);

    void update(const sp<_Long> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(int i);
    
    static long parseDecLong(const sp<_String>&);

    static long parseHexLong(const sp<_String>&);

    static long parseOctLong(const sp<_String>&);

    static long parseBinaryLong(const sp<_String>&);

    static sp<_String> className();
    
    uint64_t hashcode();

    ~_Long();

private:
    long val;
};

}
#endif
