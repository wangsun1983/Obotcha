#include "Uint32.hpp"

namespace obotcha {

_Uint32::_Uint32(uint32_t v) : val(v) {}

_Uint32::_Uint32(Uint32 v) {
    if(v == nullptr) {
        val = 0;
        return;
    }
    
    val = v->val;
}
    
uint32_t _Uint32::toValue() {
    return val;
}

bool _Uint32::equals(Uint32 p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint32::equals(uint32_t p) {
    return val == p;
}

bool _Uint32::equals(_Uint32 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint32::~_Uint32() {
}

}
