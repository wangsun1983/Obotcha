#include "Long.hpp"

namespace obotcha {

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

bool _Long::equals(_Long *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Long::~_Long() {
}

}