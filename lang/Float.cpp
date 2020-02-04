#include <cmath>
#include "Float.hpp"
#include "InitializeException.hpp"

namespace obotcha {

const float _Float::EPS = 1e-6;

_Float::_Float(float v) : val(v) {

}

_Float::_Float(Float &v){
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }

    val = v->val;
}

float _Float::toValue() {
    return val;
}

bool _Float::equals(Float &p) {
    if(p == nullptr) {
        return false;
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

_Float::~_Float() {
}

}