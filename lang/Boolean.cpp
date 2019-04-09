#include "Boolean.hpp"

namespace obotcha {

_Boolean::_Boolean(bool v) : val(v) {}

_Boolean::_Boolean(Boolean v) {
    val = v->val;
}
    
bool _Boolean::toValue() {
    return val;
}

bool _Boolean::equals(Boolean p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Boolean::equals(_Boolean *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Boolean::equals(bool p) {
    return val == p;
}

_Boolean::~_Boolean() {
}

}