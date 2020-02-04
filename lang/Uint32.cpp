/**
 * @file Uint32.cpp
 * @brief this class used for uint32
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Uint32.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_Uint32::_Uint32(uint32_t v) : val(v) {}

_Uint32::_Uint32(Uint32 &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }
    
    val = v->val;
}
    
uint32_t _Uint32::toValue() {
    return val;
}

bool _Uint32::equals(Uint32 &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint32::equals(uint32_t p) {
    return val == p;
}

bool _Uint32::equals(const _Uint32 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint32::~_Uint32() {
}

}
