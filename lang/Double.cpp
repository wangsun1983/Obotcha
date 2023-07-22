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

_Double::_Double() : mValue(0.0) {}

_Double::_Double(double v) : mValue(v) {}

_Double::_Double(const Double &v) {
    Panic(v == nullptr,InitializeException, "Object is null");
    mValue = v->mValue;
}

double _Double::toValue() { 
    return mValue; 
}

bool _Double::equals(Object p) {
    auto v = dynamic_cast<_Double *>(p.get_pointer());
    return v != nullptr && IsEqual(mValue,v->mValue); 
}

bool _Double::IsEqual(double x, double y) {
    static int ulp = 2;
    // return std::fabs(val-p) <= std::numeric_limits<double>::epsilon();
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <=
               std::numeric_limits<double>::epsilon() * std::fabs(x + y) * ulp
           // unless the result is subnormal
           || std::fabs(x - y) < std::numeric_limits<double>::min();
}

sp<_Double> _Double::Parse(sp<_String> s) {
    Panic(s == nullptr,NullPointerException, "Object is null");
    NoException(
        double v = _Number<double>::ParseNumber(s->getStdString(),32);
        return createDouble(v);
    );

    return nullptr;
}

void _Double::update(double v) { 
    this->mValue = v; 
}

void _Double::update(const sp<_Double> &v) { 
    this->mValue = v->mValue; 
}

sp<_String> _Double::ClassName() { 
    return createString("Double"); 
}

sp<_String> _Double::toString() { 
    return createString(mValue); 
}

uint64_t _Double::hashcode() const { 
    return std::hash<double>{}(mValue);
}


} // namespace obotcha