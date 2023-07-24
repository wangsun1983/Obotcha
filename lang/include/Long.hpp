#ifndef __OBOTCHA_LONG_HPP__
#define __OBOTCHA_LONG_HPP__

#include <stdio.h>

#include "Number.hpp"
#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Long) IMPLEMENTS(Number)<long> {
public:
    static const int __isReflected = 1;

    _Long();

    explicit _Long(long v);

    explicit _Long(const Long &v);

    long toValue();

    bool equals(Object p) override;

    bool sameAs(long p);

    void update(long v);

    void update(const sp<_Long> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString() override;

    uint64_t hashcode() const override;

    ~_Long() = default;

    static sp<_String> ToString(int i);

    static sp<_Long> ParseDecLong(const sp<_String> &);

    static sp<_Long> ParseHexLong(const sp<_String> &);

    static sp<_Long> ParseOctLong(const sp<_String> &);

    static sp<_Long> ParseBinaryLong(const sp<_String> &);

    static sp<_String> ClassName();

private:
    long val;
};

} // namespace obotcha
#endif
