#include "Double.hpp"

_Double::_Double(double v) : val(v) {}

_Double::_Double(Double v) {
    val = v->val;
}
    
double _Double::toValue() {
    return val;
}

bool _Double::equals(Double p) {
    return val == p->val;
}

bool _Double::equals(double p) {
    return val == p;
}

_Double::~_Double() {
}