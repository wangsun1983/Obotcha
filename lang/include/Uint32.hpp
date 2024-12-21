#ifndef __OBOTCHA_UINT32_HPP__
#define __OBOTCHA_UINT32_HPP__

#include <stdint.h>
#include <stdio.h>

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Uint32) {
public:
    static const int __isReflected = 1;

    _Uint32() = default;

    explicit _Uint32(uint32_t v);

    explicit _Uint32(const Uint32 &v);

    uint32_t toValue() const;

    bool equals(Object p) override;

    bool sameAs(uint32_t p) const;

    void update(uint32_t v);

    void update(const sp<_Uint32> &v);

    sp<_String> toHexString() const;

    sp<_String> toOctalString() const;

    sp<_String> toBinaryString() const;

    sp<_String> toString() override;

    static sp<_String> ToString(uint32_t i);

    static sp<_Uint32> Parse(const sp<_String> &);

    static sp<_Uint32> ParseDecString(const sp<_String> &);

    static sp<_Uint32> ParseHexString(const sp<_String> &);

    static sp<_Uint32> ParseOctString(const sp<_String> &);

    static sp<_Uint32> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode() const override;

    static const uint32_t kMaxValue = 0xFFFFFFFF;

    static const uint32_t kMinValue = 0x0;

private:
    uint32_t mValue = 0;
};

} // namespace obotcha
#endif
