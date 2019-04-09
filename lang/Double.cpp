#include "Double.hpp"

namespace obotcha {

_Double::_Double(double v) : val(v) {}

_Double::_Double(Double v) {
    val = v->val;
}
    
double _Double::toValue() {
    return val;
}

bool _Double::equals(Double p) {
    if(p == nullptr) {
        return false;
    }
    
    return val == p->val;
}

bool _Double::equals(double p) {
    return val == p;
}

bool _Double::equals(_Double *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

_Double::~_Double() {
}

}