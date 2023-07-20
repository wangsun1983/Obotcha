#ifndef __OBOTCHA_FLOAT_HPP__
#define __OBOTCHA_FLOAT_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Float) {

public:
    static const int __isReflected = 1;

    _Float();

    explicit _Float(float v);

    explicit _Float(Float & v);

    float toValue();

    bool equals(Float & p);

    bool equals(const _Float *p);

    bool equals(float p);

    void update(float v);

    void update(sp<_Float> v);

    uint64_t hashcode();

    sp<_String> toString();

    ~_Float() = default;

    static bool IsEqual(float, float);

    static sp<_Float> Parse(sp<_String>);

    static sp<_String> ClassName();

private:
    float val;
};

} // namespace obotcha
#endif