#include "Uint8.hpp"

namespace obotcha {

_Uint8::_Uint8(uint8_t v) : val(v) {}

_Uint8::_Uint8(Uint8 v) {
    if(v == nullptr) {
        val = 0;
        return;
    }
    
    val = v->val;
}
    
uint8_t _Uint8::toValue() {
    return val;
}

bool _Uint8::equals(Uint8 p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint8::equals(uint8_t p) {
    return val == p;
}

bool _Uint8::equals(_Uint8 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint8::~_Uint8() {
}

}
