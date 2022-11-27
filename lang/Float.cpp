#include <algorithm>
#include <cmath>
#include <limits>

#include "Float.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "Number.hpp"

namespace obotcha {

_Float::_Float() : val(0) {

}

_Float::_Float(float v) : val(v) {

}

_Float::_Float(Float &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null");
    }

    val = v->val;
}

float _Float::toValue() {
    return val;
}

sp<_Float> _Float::parse(sp<_String> s) {
    if(s == nullptr) {
        Trigger(NullPointerException, "Object is null");
    }

    try {
        float v = _Number<float>::parseNumber(s->getStdString());
        return createFloat(v);
    } catch (int e) {
    }

    return nullptr;
}

bool _Float::isEqual(float x, float y) {
    static int ulp = 2;
    // return std::fabs(val-p) <= std::numeric_limits<double>::epsilon();
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <=
               std::numeric_limits<float>::epsilon() * std::fabs(x + y) * ulp
           // unless the result is subnormal
           || std::fabs(x - y) < std::numeric_limits<float>::min();
}

bool _Float::equals(Float &p) { 
    return isEqual(p->val, val); 
}

bool _Float::equals(const _Float *p) { 
    return isEqual(p->val, val); 
}

bool _Float::equals(float p) { 
    return isEqual(val, p); 
}

uint64_t _Float::hashcode() { 
    return std::hash<float>{}(val); 
}

String _Float::toString() { 
    return createString(this->val); 
}

void _Float::update(float v) { 
    val = v; 
}

void _Float::update(sp<_Float> v) { 
    val = v->val; 
}

sp<_String> _Float::className() { 
    return createString("Float"); 
}

_Float::~_Float() {}

} // namespace obotcha
