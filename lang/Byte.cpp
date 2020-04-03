/**
 * @file Double.cpp
 * @brief this class used for Double
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_198３＠yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */


#include "Byte.hpp"
#include "InitializeException.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_Byte::_Byte(byte v) : val(v) {}

_Byte::_Byte(Byte &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }
    val = v->val;
}
    
byte _Byte::toValue() {
    return val;
}

bool _Byte::equals(Byte &p) {
    if(p == nullptr) {
        throw IllegalArgumentException("byte equal null");
    }
    
    return val == p->val;
}

bool _Byte::equals(byte p) {
    return val == p;
}

bool _Byte::equals(const _Byte *p) {
    if(p == nullptr) {
        throw IllegalArgumentException("byte equal null");
    }

    return val == p->val;
}

void _Byte::update(byte v) {
    val = v;
}

void _Byte::update(sp<_Byte>v) {
    if(v == nullptr) {
        throw IllegalArgumentException("byte equal null");
    }

    val = v->val;
}

_Byte::~_Byte() {
}

}