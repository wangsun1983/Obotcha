#ifndef __OBOTCHA_UINT64_HPP__
#define __OBOTCHA_UINT64_HPP__

#include <stdint.h>
#include <stdio.h>

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Uint64) {
public:
    static const int __isReflected = 1;

    _Uint64() = default;

    explicit _Uint64(uint64_t v);

    explicit _Uint64(const Uint64 &v);

    uint64_t toValue() const;

    bool equals(Object p) override;

    bool sameAs(uint64_t p) const;

    void update(uint64_t v);

    void update(const sp<_Uint64> &v);

    sp<_String> toHexString() const;

    sp<_String> toOctalString() const;

    sp<_String> toBinaryString() const;

    sp<_String> toString() override;
    
    uint64_t hashcode() const override;

    ~_Uint64() override = default;

    static sp<_String> ToString(uint64_t i);

    static sp<_Uint64> Parse(const sp<_String> &);

    static sp<_Uint64> ParseDecString(const sp<_String> &);

    static sp<_Uint64> ParseHexString(const sp<_String> &);

    static sp<_Uint64> ParseOctString(const sp<_String> &);

    static sp<_Uint64> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    static const uint64_t kMaxValue = 0xFFFFFFFFFFFFFFFF;

    static const uint64_t kMinValue = 0x0;

  private:
    uint64_t mValue = 0;
};

} // namespace obotcha
#endif
