#ifndef __OBOTCHA_UINT8_HPP__
#define __OBOTCHA_UINT8_HPP__

#include <stdint.h>
#include <stdio.h>

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Uint8) {
public:
    static const int __isReflected = 1;

    _Uint8() = default;

    explicit _Uint8(uint8_t v);

    explicit _Uint8(const Uint8 &v);

    uint8_t toValue() const;

    bool equals(Object p) override;

    bool sameAs(uint8_t p) const;

    void update(uint8_t v);

    void update(const sp<_Uint8> &v);

    sp<_String> toHexString() const;

    sp<_String> toOctalString() const;

    sp<_String> toBinaryString() const;

    sp<_String> toString() override;

    static sp<_String> ToString(uint8_t i);

    static sp<_Uint8> Parse(const sp<_String> &);

    static sp<_Uint8> ParseDecString(const sp<_String> &);

    static sp<_Uint8> ParseHexString(const sp<_String> &);

    static sp<_Uint8> ParseOctString(const sp<_String> &);

    static sp<_Uint8> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode() const override;

    static const uint8_t kMaxValue = 0xFF;

    static const uint8_t kMinValue = 0x0;

private:
    uint8_t mValue;
};

} // namespace obotcha
#endif
