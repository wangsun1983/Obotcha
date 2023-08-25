#ifndef __OBOTCHA_LONG_HPP__
#define __OBOTCHA_LONG_HPP__

#include <stdio.h>

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Long) {
public:
    static const int __isReflected = 1;
    
    _Long() = default;

    explicit _Long(long v);

    explicit _Long(const Long &v);

    long toValue() const;

    bool equals(Object p) override;

    bool sameAs(long p) const;

    void update(long v);

    void update(const sp<_Long> &v);

    sp<_String> toHexString() const;

    sp<_String> toOctalString() const;

    sp<_String> toBinaryString() const;

    sp<_String> toString() override;

    uint64_t hashcode() const override;

    ~_Long() override = default;

    static sp<_String> ToString(int i);

    static sp<_Long> ParseDecLong(const sp<_String> &);

    static sp<_Long> ParseHexLong(const sp<_String> &);

    static sp<_Long> ParseOctLong(const sp<_String> &);

    static sp<_Long> ParseBinaryLong(const sp<_String> &);

    static sp<_String> ClassName();

private:
    long mValue = 0;
};

} // namespace obotcha
#endif
