#include "Float.hpp"
#include "String.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "NumberTransformer.hpp"

namespace obotcha {

const float _Float::kMaxValue = 3.4028235E38f;
const float _Float::kMinValue = 1.4E-45f;
const float _Float::kUlp = 2;

_Float::_Float(float v) : mValue(v) {
}

_Float::_Float(const Float &v) {
    Panic(v == nullptr,InitializeException, "Object is null")
    mValue = v->mValue;
}

float _Float::toValue() const {
    return mValue;
}

sp<_Float> _Float::Parse(sp<_String> s) {
    Panic(s == nullptr,NullPointerException, "Object is null")
    try {
        auto v = st(NumberTransformer)::ParseNumber<float>(s->getStdString(),16);
        return createFloat(v);
    } catch(TransformException &) {
        return nullptr;
    }
}

bool _Float::equals(Object p) { 
    auto v = dynamic_cast<_Float *>(p.get_pointer());
    return v != nullptr && Compare(mValue,v->mValue) == 0; 
}

bool _Float::sameAs(float v) const { 
    return Compare(v, mValue) == 0; 
}

uint64_t _Float::hashcode() const { 
    return std::hash<float>{}(mValue); 
}

String _Float::toString() { 
    return createString(mValue); 
}

void _Float::update(float v) { 
    mValue = v; 
}

void _Float::update(sp<_Float> v) { 
    mValue = v->mValue; 
}

sp<_String> _Float::ClassName() { 
    return createString("Float"); 
}

int _Float::compareTo(float value) const {
    return Compare(mValue,value);
}

int _Float::Compare(float f1,float f2) {
    // the machine epsilon has to be scaled to the magnitude of the values used
    // and multiplied by the desired precision in ULPs (units in the last place)
    if(std::fabs(f1 - f2) <
               std::numeric_limits<float>::epsilon() * std::fabs(f1 + f2) * kUlp
           // unless the result is subnormal
           || std::fabs(f1 - f2) < std::numeric_limits<float>::min()) {
        return 0;
    }

    if (std::isgreater(f1, f2)) {
        return 1;
    }

    return -1;
}

} // namespace obotcha
