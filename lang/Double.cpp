/**
 * @file Double.cpp
 * @brief this class used for Double
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <cmath>
#include "Double.hpp"


namespace obotcha {

const double _Double::EPS = 1e-8;

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
    
    return std::fabs(val-p->val) <= EPS;
}

bool _Double::equals(double p) {
    return std::fabs(val-p) <= EPS;
}

bool _Double::equals(_Double *p) {
    if(p == nullptr) {
        return false;
    }

    return std::fabs(val-p->val) <= EPS;
}

_Double::~_Double() {
}

}