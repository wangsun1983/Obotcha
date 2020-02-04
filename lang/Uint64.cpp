/**
 * @file Uint64.cpp
 * @brief this class used for uint64
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Uint64.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_Uint64::_Uint64(uint64_t v) : val(v) {}

_Uint64::_Uint64(Uint64 &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }
    
    val = v->val;
}
    
uint64_t _Uint64::toValue() {
    return val;
}

bool _Uint64::equals(Uint64 &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Uint64::equals(uint64_t p) {
    return val == p;
}

bool _Uint64::equals(const _Uint64 *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;

}

_Uint64::~_Uint64() {
}

}
