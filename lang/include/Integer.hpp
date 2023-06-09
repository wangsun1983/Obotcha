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

    _Integer();

    _Integer(int v);

    _Integer(const Integer &v);

    int toValue();

    bool equals(const Integer &p);

    bool equals(int p);

    bool equals(const _Integer *p);

    void update(int v);

    void update(const sp<_Integer> &v);

    sp<_String> toHexString();

    sp<_String> toOctalString();

    sp<_String> toBinaryString();

    sp<_String> toString();

    static sp<_String> toString(int i);

    static sp<_Integer> Parse(const sp<_String> &);

    static sp<_Integer> ParseDecString(const sp<_String> &);

    static sp<_Integer> ParseHexString(const sp<_String> &);

    static sp<_Integer> ParseOctString(const sp<_String> &);

    static sp<_Integer> ParseBinaryString(const sp<_String> &);

    static sp<_String> ClassName();

    uint64_t hashcode();

    ~_Integer();

    static const int MAX_VALUE;

    static const int MIN_VALUE;

private:
    int val;
};

} // namespace obotcha
#endif
