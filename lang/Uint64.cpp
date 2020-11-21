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
#include "NullPointerException.hpp"

namespace obotcha {

_Uint64::_Uint64(uint64_t v) : val(v) {}

_Uint64::_Uint64(Uint64 &v) {
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }
    
    val = v->val;
}
    
uint64_t _Uint64::toValue() {
    return val;
}

bool _Uint64::equals(Uint64 &p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"Object is null");
    }

    return val == p->val;
}

bool _Uint64::equals(uint64_t p) {
    return val == p;
}

bool _Uint64::equals(const _Uint64 *p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"Object is null");
    }

    return val == p->val;
}

void _Uint64::update(uint64_t v) {
    val = v;
}

void _Uint64::update(sp<_Uint64> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"Uint64 update nullptr");
    }

    val = v->val;
}

sp<_String> _Uint64::toHexString() {
    return createString(_Number::toHexString(val));
}

sp<_String> _Uint64::toOctalString() {
    return createString(_Number::toOctalString(val));
}

sp<_String> _Uint64::toBinaryString() {
    return createString(_Number::toBinaryString(val));
}

sp<_String> _Uint64::toString() {
    return createString(_Number::toDecString(val));
}

sp<_String> _Uint64::toString(uint64_t i) {
    return createString(_Number::toDecString(i));
}

uint64_t _Uint64::parseDecUint64(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseDecUint64 nullptr");
    }

    return _Number::parseDecNumber(v->getStdString());
}

uint64_t _Uint64::parseHexUint64(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseHexUint64 nullptr");
    }
    
    return _Number::parseHexNumber(v->getStdString());
}

uint64_t _Uint64::parseOctUint64(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseOctUint64 nullptr");
    }
    
    return _Number::parseOctNumber(v->getStdString());
}

uint64_t _Uint64::parseBinaryUint64(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseBinaryUint64 nullptr");
    }
    
    return _Number::parseBinaryNumber(v->getStdString());
}


_Uint64::~_Uint64() {
}

}
