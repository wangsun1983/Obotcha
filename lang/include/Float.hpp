#ifndef __OBOTCHA_FLOAT_HPP__
#define __OBOTCHA_FLOAT_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Float) {

public:
    static const int __isReflected = 1;

    _Float() = default;

    explicit _Float(float v);

    explicit _Float(const Float & v);

    float toValue() const;

    bool equals(Object p) override;

    bool sameAs(float v) const;

    void update(float v);

    void update(sp<_Float> v);

    uint64_t hashcode() const override;

    sp<_String> toString() override;

    ~_Float() override = default;

    static bool IsEqual(float, float);

    static sp<_Float> Parse(sp<_String>);

    static sp<_String> ClassName();

private:
    float val = 0.0;
};

} // namespace obotcha
#endif