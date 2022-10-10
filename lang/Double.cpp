/**
 * @file Double.cpp
 * @brief this class used for Double
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <algorithm>
#include <cmath>
#include <limits>

#include "Double.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

_Double::_Double() : val(0.0) {}

_Double::_Double(double v) : val(v) {}

_Double::_Double(const Double &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null");
    }
    val = v->val;
}

double _Double::toValue() { return val; }

bool _Double::equals(const Double &p) { return equals(p->val); }

bool _Double::equals(double p) { return isEqual(val, p); }

bool _Double::isEqual(double x, double y) {
    static int ulp = 2;
    // return std::fabs(val-p) <= std::numeric_limits<double>::epsilon();
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <=
               std::numeric_limits<double>::epsilon() * std::fabs(x + y) * ulp
           // unless the result is subnormal
           || std::fabs(x - y) < std::numeric_limits<double>::min();
}

sp<_Double> _Double::parse(sp<_String> s) {
    if (s == nullptr) {
        Trigger(NullPointerException, "Object is null");
    }

    try {
        double v = _Number<double>::parseNumber(s->getStdString());
        return createDouble(v);
    } catch (int e) {
    }

    return nullptr;
}

bool _Double::equals(const _Double *p) { 
    return equals(p->val); 
}

void _Double::update(double v) { 
    this->val = v; 
}

void _Double::update(const sp<_Double> &v) { 
    this->val = v->val; 
}

sp<_String> _Double::className() { 
    return createString("Double"); 
}

sp<_String> _Double::toString() { 
    return createString(val); 
}

uint64_t _Double::hashcode() { 
    return std::hash<double>{}(val);
}

_Double::~_Double() {}

} // namespace obotcha