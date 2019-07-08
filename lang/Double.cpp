/**
 * @file Double.cpp
 * @brief this class used for Double
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_198£³£Àyahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */


#include "Double.hpp"

namespace obotcha {

_Double::_Double(double v) : val(v) {}

_Double::_Double(Double v) {
    val = v->val;
}
    
double _Double::toValue() {
    return val;
}

bool _Double::equals(Double p) {
    if(p == nullptr) {
        return false;
    }
    
    return val == p->val;
}

bool _Double::equals(double p) {
    return val == p;
}

bool _Double::equals(_Double *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

_Double::~_Double() {
}

}