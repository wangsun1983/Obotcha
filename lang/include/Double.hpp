#ifndef __OBOTCHA_DOUBLE_HPP__
#define __OBOTCHA_DOUBLE_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Double) {
public:
    static const int __isReflected = 1;

    _Double();

    _Double(double v);

    _Double(const Double &v);

    double toValue();

    void update(double);

    void update(const sp<_Double> &);

    bool equals(double p);

    bool equals(const Double &p);

    bool equals(const _Double *p);

    static bool isEqual(double, double);

    static sp<_Double> parse(sp<_String>);

    sp<_String> toString();

    static sp<_String> className();

    uint64_t hashcode();

    ~_Double();

private:
    double val;
};

} // namespace obotcha
#endif