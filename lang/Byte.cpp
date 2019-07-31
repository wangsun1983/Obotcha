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

namespace obotcha {

_Byte::_Byte(byte v) : val(v) {}

_Byte::_Byte(Byte v) {
    val = v->val;
}
    
byte _Byte::toValue() {
    return val;
}

bool _Byte::equals(Byte p) {
    if(p == nullptr) {
        return false;
    }
    
    return val == p->val;
}

bool _Byte::equals(byte p) {
    return val == p;
}

bool _Byte::equals(_Byte *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

_Byte::~_Byte() {
}

}