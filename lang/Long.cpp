/**
 * @file Long.cpp
 * @brief this class used for long
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Long.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_Long::_Long(long v) : val(v) {}

_Long::_Long(Long &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }
    
    val = v->val;
}
    
long _Long::toValue() {
    return val;
}

bool _Long::equals(Long &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Long::equals(long p) {
    return val == p;
}

bool _Long::equals(const _Long *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

_Long::~_Long() {
}

}