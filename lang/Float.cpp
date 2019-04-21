#include "Float.hpp"

namespace obotcha {

_Float::_Float(float v) : val(v) {

}

_Float::_Float(Float v){
    if(v == nullptr) {
        val = 0;
        return;
    }

    val = v->val;
}

float _Float::toValue() {
    return val;
}

bool _Float::equals(Float p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Float::equals(float p) {
    return val == p;
}

_Float::~_Float() {
}

}