#ifndef __OBOTCHA_UINT32_HPP__
#define __OBOTCHA_UINT32_HPP__

#include <stdint.h>
#include <stdio.h>

#include "Number.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Uint32) IMPLEMENTS(Number<uint32_t>) {
public:
    static const int __isReflected = 1;

    _Uint32();

    _Uint32(uint32_t v);

    _Uint32(const Uint32 &v);

    uint32_t toValue();

    bool equals(const Uint32 &p);

    bool equals(uint32_t p);

    bool equals(const _Uint32 *p);

    void update(uint32_t v);

    void update(const sp<_Uint32> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> ToString(uint32_t i);

    static sp<_Uint32> Parse(const sp<_String> &);

    static sp<_Uint32> ParseDecString(const sp<_String> &);

    static sp<_Uint32> ParseHexString(const sp<_String> &);

    static sp<_Uint32> ParseOctString(const sp<_String> &);

    static sp<_Uint32> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode();

    ~_Uint32();

    static const uint32_t MAX_VALUE = 0xFFFFFFFF;

    static const uint32_t MIN_VALUE = 0x0;

private:
    uint32_t val;
};

} // namespace obotcha
#endif
