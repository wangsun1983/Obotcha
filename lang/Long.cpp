#include "Long.hpp"

_Long::_Long(long v) : val(v) {}

_Long::_Long(Long v) {
    val = v->val;
}
    
long _Long::toValue() {
    return val;
}

bool _Long::equals(Long p) {
    return val == p->val;
}

bool _Long::equals(long p) {
    return val == p;
}

_Long::~_Long() {
}