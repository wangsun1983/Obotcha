/**
 * @file Uint16.cpp
 * @brief this class used for uint16
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Uint16.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_Uint16::_Uint16(uint16_t v) : val(v) {}

_Uint16::_Uint16(Uint16 &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }
    
    val = v->val;
}
    
uint16_t _Uint16::toValue() {
    return val;
}

bool _Uint16::equals(Uint16 &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint16::equals(uint16_t p) {
    return val == p;
}

bool _Uint16::equals(const _Uint16 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint16::~_Uint16() {
}

}
