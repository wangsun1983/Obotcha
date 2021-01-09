/**
 * @file Uint16.cpp
 * @brief this class used for uint16
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Uint16.hpp"
#include "InitializeException.hpp"
#include "Number.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

_Uint16::_Uint16():val(0) {

}

_Uint16::_Uint16(uint16_t v) : val(v) {}

_Uint16::_Uint16(Uint16 &v) {
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }
    
    val = v->val;
}
    
uint16_t _Uint16::toValue() {
    return val;
}

bool _Uint16::equals(Uint16 &p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"Object is null");
    }

    return val == p->val;
}

bool _Uint16::equals(uint16_t p) {
    return val == p;
}

bool _Uint16::equals(const _Uint16 *p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"Object is null");
    }

    return val == p->val;
}

void _Uint16::update(uint16_t v) {
    val = v;
}

void _Uint16::update(sp<_Uint16> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"Uint16 update nullptr");
    }

    val = v->val;
}

sp<_String> _Uint16::toHexString() {
    return createString(_Number::toHexString(val));
}

sp<_String> _Uint16::toOctalString() {
    return createString(_Number::toOctalString(val));
}

sp<_String> _Uint16::toBinaryString() {
    return createString(_Number::toBinaryString(val));
}

sp<_String> _Uint16::toString() {
    return createString(_Number::toDecString(val));
}

sp<_String> _Uint16::toString(uint16_t i) {
    return createString(_Number::toDecString(i));
}

uint16_t _Uint16::parseDecUint16(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseDecUint16 nullptr");
    }

    return _Number::parseDecNumber(v->getStdString());
}

uint16_t _Uint16::parseHexUint16(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseHexUint16 nullptr");
    }
    
    return _Number::parseHexNumber(v->getStdString());
}

uint16_t _Uint16::parseOctUint16(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseOctUint16 nullptr");
    }
    
    return _Number::parseOctNumber(v->getStdString());
}

uint16_t _Uint16::parseBinaryUint16(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseBinaryUint16 nullptr");
    }
    
    return _Number::parseBinaryNumber(v->getStdString());
}

sp<_String> _Uint16::className() {
    return createString("Uint16");
}

_Uint16::~_Uint16() {
}

}
