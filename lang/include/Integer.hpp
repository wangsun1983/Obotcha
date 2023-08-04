#ifndef __OBOTCHA_INTEGER_HPP__
#define __OBOTCHA_INTEGER_HPP__

#include <sstream>
#include <stdio.h>

#include "Number.hpp"
#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Integer) IMPLEMENTS(Number)<int> {
public:
    static const int __isReflected = 1;

    _Integer() = default;

    explicit _Integer(int v);

    explicit _Integer(const Integer &v);

    int toValue() const;

    bool equals(Object p) override;

    bool sameAs(int p) const;

    void update(int v);

    void update(const sp<_Integer> &v);

    sp<_String> toHexString() const;

    sp<_String> toOctalString() const;

    sp<_String> toBinaryString() const;

    sp<_String> toString() override;

    uint64_t hashcode() const override;

    ~_Integer() override = default;

    static sp<_String> ToString(int i);

    static sp<_Integer> Parse(const sp<_String> &);

    static sp<_Integer> ParseDecString(const sp<_String> &);

    static sp<_Integer> ParseHexString(const sp<_String> &);

    static sp<_Integer> ParseOctString(const sp<_String> &);

    static sp<_Integer> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    static const int kMaxValue;

    static const int kMinValue;

private:
    int mValue = 0;
};

} // namespace obotcha
#endif
