#include <cmath>
#include <algorithm>

#include "Float.hpp"
#include "InitializeException.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

const float _Float::EPS = 1e-6;

_Float::_Float():val(0) {}

_Float::_Float(float v) : val(v) {

}

_Float::_Float(Float &v){
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }

    val = v->val;
}

float _Float::toValue() {
    return val;
}

bool _Float::equals(Float &p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"p is null");
    }

    return std::fabs(val-p->val) <= EPS;
}

bool _Float::equals(const _Float *p) {
    if(p == nullptr) {
        return false;
    }

    return std::fabs(val-p->val) <= EPS;
}

bool _Float::equals(float p) {
    return std::fabs(val-p) <= EPS;
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
    if(v == nullptr) {
        Trigger(NullPointerException,"Float equals nullptr"); 
    }

    val = v->val;
}

sp<_String> _Float::className() {
    return createString("Float");
}

_Float::~_Float() {
}

}