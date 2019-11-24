/**
 * @file Integer.cpp
 * @brief this class used for int
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <sstream>

#include "Integer.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_Integer::_Integer(int v) : val(v) {

}

_Integer::_Integer(Integer &v) {
    if(v == nullptr) {
        throw createInitializeException("Object is null");
    }

    val = 0;
}

int _Integer::toValue() {
    return val;
}

bool _Integer::equals(Integer &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Integer::equals(int p) {
    return val == p;
}

bool _Integer::equals(const _Integer *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

_Integer::~_Integer() {
}

}