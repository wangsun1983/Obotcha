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
#include "NullPointerException.hpp"

namespace obotcha {

_Uint32::_Uint32():val(0) {

}

_Uint32::_Uint32(uint32_t v) : val(v) {}

_Uint32::_Uint32(Uint32 &v) {
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }
    
    val = v->val;
}
    
uint32_t _Uint32::toValue() {
    return val;
}

bool _Uint32::equals(Uint32 &p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"Object is null");
    }

    return val == p->val;
}

bool _Uint32::equals(uint32_t p) {
    return val == p;
}

bool _Uint32::equals(const _Uint32 *p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"Object is null");
    }

    return val == p->val;
}

void _Uint32::update(uint32_t v) {
    val = v;
}

void _Uint32::update(sp<_Uint32> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"Uint32 update nullptr");
    }

    val = v->val;
}

sp<_String> _Uint32::toHexString() {
    return createString(_Number::toHexString(val));
}

sp<_String> _Uint32::toOctalString() {
    return createString(_Number::toOctalString(val));
}

sp<_String> _Uint32::toBinaryString() {
    return createString(_Number::toBinaryString(val));
}

sp<_String> _Uint32::toString() {
    return createString(_Number::toDecString(val));
}

sp<_String> _Uint32::toString(uint32_t i) {
    return createString(_Number::toDecString(i));
}

uint32_t _Uint32::parseDecUint32(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseDecUint32 nullptr");
    }

    return _Number::parseDecNumber(v->getStdString());
}

uint32_t _Uint32::parseHexUint32(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseHexUint32 nullptr");
    }
    
    return _Number::parseHexNumber(v->getStdString());
}

uint32_t _Uint32::parseOctUint32(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseOctUint32 nullptr");
    }
    
    return _Number::parseOctNumber(v->getStdString());
}

uint32_t _Uint32::parseBinaryUint32(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseBinaryUint32 nullptr");
    }
    
    return _Number::parseBinaryNumber(v->getStdString());
}

_Uint32::~_Uint32() {
}

}
