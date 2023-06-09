#ifndef __OBOTCHA_UINT8_HPP__
#define __OBOTCHA_UINT8_HPP__

#include <stdint.h>
#include <stdio.h>

#include "Number.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Uint8) IMPLEMENTS(Number<uint8_t>) {
public:
    static const int __isReflected = 1;

    _Uint8();

    _Uint8(uint8_t v);

    _Uint8(const Uint8 &v);

    uint8_t toValue();

    bool equals(const Uint8 &p);

    bool equals(uint8_t p);

    bool equals(const _Uint8 *p);

    void update(uint8_t v);

    void update(const sp<_Uint8> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(uint8_t i);

    static sp<_Uint8> Parse(const sp<_String> &);

    static sp<_Uint8> ParseDecString(const sp<_String> &);

    static sp<_Uint8> ParseHexString(const sp<_String> &);

    static sp<_Uint8> ParseOctString(const sp<_String> &);

    static sp<_Uint8> ParseBinaryString(const sp<_String> &);

    static sp<_String> className();

    uint64_t hashcode();

    static const uint8_t MAX_VALUE = 0xFF;

    static const uint8_t MIN_VALUE = 0x0;

    ~_Uint8();

private:
    uint8_t val;
};

} // namespace obotcha
#endif
