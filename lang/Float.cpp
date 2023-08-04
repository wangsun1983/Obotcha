#include <algorithm>
#include <cmath>
#include <limits>

#include "Float.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "Number.hpp"

namespace obotcha {

const float _Float::kMaxValue = 3.4028235E38f;
const float _Float::kMinValue = 1.4E-45f;

_Float::_Float(float v) : val(v) {
}

_Float::_Float(const Float &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null")
    }

    val = v->val;
}

float _Float::toValue() const {
    return val;
}

sp<_Float> _Float::Parse(sp<_String> s) {
    Panic(s == nullptr,NullPointerException, "Object is null")
    NoException(
        float v = _Number<float>::ParseNumber(s->getStdString(),16);
        return createFloat(v);
    )
    return nullptr;
}

bool _Float::IsEqual(float x, float y) {
    static int ulp = 2;
    // return std::fabs(val-p) <= std::numeric_limits<double>::epsilon();
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    return std::fabs(x - y) <=
               std::numeric_limits<float>::epsilon() * std::fabs(x + y) * ulp
           // unless the result is subnormal
           || std::fabs(x - y) < std::numeric_limits<float>::min();
}

bool _Float::equals(Object p) { 
    auto v = dynamic_cast<_Float *>(p.get_pointer());
    return v != nullptr && IsEqual(val,v->val); 
}

bool _Float::sameAs(float v) const { 
    return IsEqual(v, val); 
}

uint64_t _Float::hashcode() const { 
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

sp<_String> _Float::ClassName() { 
    return createString("Float"); 
}

} // namespace obotcha
