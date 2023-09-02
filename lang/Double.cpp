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
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"
#include "NumberTransformer.hpp"

namespace obotcha {

const double _Double::kMaxValue = 1.7976931348623157E308;
const double _Double::kMinValue = 4.9E-324;

_Double::_Double(double v) : mValue(v) {
}

_Double::_Double(const Double &v) {
    Panic(v == nullptr,InitializeException, "Object is null")
    mValue = v->mValue;
}

double _Double::toValue() const { 
    return mValue; 
}

bool _Double::equals(Object p) {
    auto v = dynamic_cast<_Double *>(p.get_pointer());
    return v != nullptr && Compare(mValue,v->mValue) == 0; 
}

bool _Double::sameAs(double v) const {
    return Compare(mValue,v) == 0;
}

int _Double::compareTo(double v) {
    return Compare(mValue,v);
}

sp<_Double> _Double::Parse(sp<_String> s) {
    Panic(s == nullptr,NullPointerException, "Object is null")
    try {
        auto v = st(NumberTransformer)::ParseNumber<double>(s->getStdString(),32);
        return createDouble(v);
    } catch(TransformException &) {}

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

int _Double::Compare(double f1,double f2) {
    static int ulp = 2;
    // return std::fabs(val-p) <= std::numeric_limits<double>::epsilon();
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    if(std::fabs(f1 - f2) <=
               std::numeric_limits<double>::epsilon() * std::fabs(f1 + f2) * ulp
           // unless the result is subnormal
           || std::fabs(f1 - f2) < std::numeric_limits<double>::min()) {
        return 0;
    }

    if (std::isgreater(f1, f2)) {
        return 1;
    }

    return -1;
}


} // namespace obotcha