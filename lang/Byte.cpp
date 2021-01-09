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
#include "NullPointerException.hpp"

namespace obotcha {

_Byte::_Byte():val(0) {}

_Byte::_Byte(byte v) : val(v) {}

_Byte::_Byte(Byte &v) {
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }
    val = v->val;
}
    
byte _Byte::toValue() {
    return val;
}

bool _Byte::equals(Byte &p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"byte equal null");
    }
    
    return val == p->val;
}

bool _Byte::equals(byte p) {
    return val == p;
}

bool _Byte::equals(const _Byte *p) {
    if(p == nullptr) {
        Trigger(NullPointerException,"byte equal null");
    }

    return val == p->val;
}

void _Byte::update(byte v) {
    val = v;
}

void _Byte::update(sp<_Byte>v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"byte equal null");
    }

    val = v->val;
}

sp<_String> _Byte::toHexString() {
    return createString(_Number::toHexString((int)val));
}

sp<_String> _Byte::toOctalString() {
    return createString(_Number::toOctalString((int)val));
}

sp<_String> _Byte::toBinaryString() {
    return createString(_Number::toBinaryString((int)val));
}

sp<_String> _Byte::toString() {
    return createString(_Number::toDecString((int)val));
}

sp<_String> _Byte::toString(byte i) {
    return createString(_Number::toDecString(i));
}

byte _Byte::parseDecByte(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseDecByte nullptr");
    }

    return _Number::parseDecNumber(v->getStdString());
}

byte _Byte::parseHexByte(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseHexByte nullptr");
    }
    
    return _Number::parseHexNumber(v->getStdString());
}

byte _Byte::parseOctByte(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseOctByte nullptr");
    }
    
    return _Number::parseOctNumber(v->getStdString());
}

byte _Byte::parseBinaryByte(sp<_String> v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"parseBinaryByte nullptr");
    }
    
    return _Number::parseBinaryNumber(v->getStdString());
}

sp<_String> _Byte::className() {
    return createString("Byte");
}

_Byte::~_Byte() {
}

}