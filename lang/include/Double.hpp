#ifndef __OBOTCHA_DOUBLE_HPP__
#define __OBOTCHA_DOUBLE_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Double) {
public:
    static const int __isReflected = 1;

    _Double() = default;

    explicit _Double(double v);

    explicit _Double(const Double &v);

    double toValue() const;

    void update(double);

    void update(const sp<_Double> &);

    bool equals(Object p) override;

    bool sameAs(double p) const;
    
    sp<_String> toString() override;

    uint64_t hashcode() const override;

    ~_Double() override = default;

    static bool IsEqual(double, double);

    static sp<_Double> Parse(sp<_String>);

    static sp<_String> ClassName();

    static const double kMaxValue;
    static const double kMinValue;

private:
    double mValue = 0.0;
};

} // namespace obotcha
#endif
