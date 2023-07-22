#ifndef __OBOTCHA_UINT16_HPP__
#define __OBOTCHA_UINT16_HPP__

#include <stdint.h>
#include <stdio.h>

#include "Number.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Uint16) IMPLEMENTS(Number<uint16_t>) {
public:
    static const int __isReflected = 1;

    _Uint16();

    explicit _Uint16(uint16_t v);

    explicit _Uint16(const Uint16 &v);

    uint16_t toValue();

    bool equals(Object p) override;

    // bool equals(uint16_t p);

    // bool equals(const _Uint16 *p);

    void update(uint16_t v);

    void update(const sp<_Uint16> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString() override;

    static sp<_String> ToString(uint16_t i);

    static sp<_Uint16> Parse(const sp<_String> &);

    static sp<_Uint16> ParseDecString(const sp<_String> &);

    static sp<_Uint16> ParseHexString(const sp<_String> &);

    static sp<_Uint16> ParseOctString(const sp<_String> &);

    static sp<_Uint16> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode() const override;

    ~_Uint16() = default;

    static const uint16_t MAX_VALUE = 0xFFFF;

    static const uint16_t MIN_VALUE = 0x0;

private:
    uint16_t val;
};

} // namespace obotcha
#endif
