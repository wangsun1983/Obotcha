#ifndef __OBOTCHA_UINT64_HPP__
#define __OBOTCHA_UINT64_HPP__

#include <stdio.h>
#include <stdint.h>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Number.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Uint64) IMPLEMENTS(Number<uint64_t>) {
public:
    static const int __isReflected = 1;

    _Uint64();
    
    _Uint64(uint64_t v);

    _Uint64(const Uint64 &v);

    uint64_t toValue();

    bool equals(const Uint64 &p);

    bool equals(uint64_t p);

    bool equals(const _Uint64 *p);

    void update(uint64_t v);

    void update(const sp<_Uint64> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(uint64_t i);
    
    static sp<_Uint64> parseDecUint64(const sp<_String>&);

    static sp<_Uint64> parseHexUint64(const sp<_String>&);

    static sp<_Uint64> parseOctUint64(const sp<_String>&);

    static sp<_Uint64> parseBinaryUint64(const sp<_String>&);

    static sp<_String> className();

    uint64_t hashcode();

    ~_Uint64();

    static const uint64_t MAX_VALUE = 0xFFFFFFFFFFFFFFFF;

    static const uint64_t MIN_VALUE = 0x0;

private:
    uint64_t val;
};

}
#endif
