#include "Uint16.hpp"

namespace obotcha {

_Uint16::_Uint16(uint16_t v) : val(v) {}

_Uint16::_Uint16(Uint16 v) {
    if(v == nullptr) {
        val = 0;
        return;
    }
    
    val = v->val;
}
    
uint16_t _Uint16::toValue() {
    return val;
}

bool _Uint16::equals(Uint16 p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint16::equals(uint16_t p) {
    return val == p;
}

bool _Uint16::equals(_Uint16 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint16::~_Uint16() {
}

}
