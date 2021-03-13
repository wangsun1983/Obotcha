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
#include <algorithm>
#include <cmath>

#include "Double.hpp"
#include "InitializeException.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

const double _Double::EPS = 1e-8;

_Double::_Double():val(0.0) {}

_Double::_Double(double v) : val(v) {}

_Double::_Double(Double &v) {
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }
    val = v->val;
}
    
double _Double::toValue() {
    return val;
}

bool _Double::equals(Double &p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"double update null");
    }
    
    return std::fabs(val-p->val) <= EPS;
}

bool _Double::equals(double p) {
    return std::fabs(val-p) <= EPS;
}

bool _Double::equals(const _Double *p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"double update null");
    }

    return std::fabs(val-p->val) <= EPS;
}

void _Double::update(double v) {
    this->val = v;
}

void _Double::update(sp<_Double> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"double update null");
    }

    this->val = v->val;
}

sp<_String> _Double::className() {
    return createString("Double");
}

uint64_t _Double::hashcode() {
    return std::hash<double>{}(val);
}

_Double::~_Double() {
}

}