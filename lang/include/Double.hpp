#ifndef __OBOTCHA_DOUBLE_HPP__
#define __OBOTCHA_DOUBLE_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Double) {
public:
    static const int __isReflected = 1;

    _Double();

    explicit _Double(double v);

    explicit _Double(const Double &v);

    double toValue();

    void update(double);

    void update(const sp<_Double> &);

    bool equals(Object p) override;

    bool sameAs(double p);
    //bool equals(const _Double *p);
    
    sp<_String> toString() override;

    uint64_t hashcode() const override;

    ~_Double() = default;

    static bool IsEqual(double, double);

    static sp<_Double> Parse(sp<_String>);

    static sp<_String> ClassName();

private:
    double mValue;
};

} // namespace obotcha
#endif
