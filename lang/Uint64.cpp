#include "Uint64.hpp"

namespace obotcha {

_Uint64::_Uint64(uint64_t v) : val(v) {}

_Uint64::_Uint64(Uint64 v) {
    if(v == nullptr) {
        val = 0;
        return;
    }
    
    val = v->val;
}
    
uint64_t _Uint64::toValue() {
    return val;
}

bool _Uint64::equals(Uint64 p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint64::equals(uint64_t p) {
    return val == p;
}

bool _Uint64::equals(_Uint64 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint64::~_Uint64() {
}

}
