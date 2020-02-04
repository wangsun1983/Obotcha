/**
 * @file String.cpp
 * @brief this class used for uint8
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Uint8.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_Uint8::_Uint8(uint8_t v) : val(v) {}

_Uint8::_Uint8(Uint8 &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }
    
    val = v->val;
}
    
uint8_t _Uint8::toValue() {
    return val;
}

bool _Uint8::equals(Uint8 &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint8::equals(uint8_t p) {
    return val == p;
}

bool _Uint8::equals(const _Uint8 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint8::~_Uint8() {
}

}
