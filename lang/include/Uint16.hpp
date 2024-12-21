#ifndef __OBOTCHA_UINT16_HPP__
#define __OBOTCHA_UINT16_HPP__

#include <stdint.h>
#include <stdio.h>

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Uint16) {
public:
    static const int __isReflected = 1;

    _Uint16() = default;

    explicit _Uint16(uint16_t v);

    explicit _Uint16(const Uint16 &v);

    uint16_t toValue() const;

    bool equals(Object p) override;

    bool sameAs(uint16_t p) const;

    void update(uint16_t v);

    void update(const sp<_Uint16> &v);

    sp<_String> toHexString() const;

    sp<_String> toOctalString() const;

    sp<_String> toBinaryString() const;

    sp<_String> toString() override;

    static sp<_String> ToString(uint16_t i);

    static sp<_Uint16> Parse(const sp<_String> &);

    static sp<_Uint16> ParseDecString(const sp<_String> &);

    static sp<_Uint16> ParseHexString(const sp<_String> &);

    static sp<_Uint16> ParseOctString(const sp<_String> &);

    static sp<_Uint16> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode() const override;

    static const uint16_t kMaxValue = 0xFFFF;

    static const uint16_t kMinValue = 0x0;

private:
    uint16_t mValue = 0;
};

} // namespace obotcha
#endif
