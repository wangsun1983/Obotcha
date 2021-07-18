/**
 * @file String.cpp
 * @brief this class used for uint8
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <algorithm>

#include "Uint8.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "Number.hpp"

namespace obotcha {

_Uint8::_Uint8():val(0) {

}

_Uint8::_Uint8(uint8_t v) : val(v) {}

_Uint8::_Uint8(const Uint8 &v) {
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }
    
    val = v->val;
}
    
uint8_t _Uint8::toValue() {
    return val;
}

bool _Uint8::equals(const Uint8 &p) {
    return val == p->val;
}

bool _Uint8::equals(uint8_t p) {
    return val == p;
}

bool _Uint8::equals(const _Uint8 *p) {
    return val == p->val;
}

void _Uint8::update(uint8_t v) {
    val = v;
}

void _Uint8::update(const sp<_Uint8> &v) {
    val = v->val;
}

sp<_String> _Uint8::toHexString() {
    return createString(_Number::toHexString(val));
}

sp<_String> _Uint8::toOctalString() {
    return createString(_Number::toOctalString(val));
}

sp<_String> _Uint8::toBinaryString() {
    return createString(_Number::toBinaryString(val));
}

uint64_t _Uint8::hashcode() {
    return std::hash<uint8_t>{}(val);
}

sp<_String> _Uint8::toString() {
    return createString(_Number::toDecString(val));
}

sp<_String> _Uint8::toString(uint8_t i) {
    return createString(_Number::toDecString(i));
}

sp<_Uint8> _Uint8::parseDecUint8(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint8_t value = _Number::parseDecNumber(pa->getStdString());
        return createUint8(value);
    } catch(const char *err){}

    return nullptr;
}

sp<_Uint8> _Uint8::parseHexUint8(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint8_t value = _Number::parseHexNumber(pa->getStdString());
        return createUint8(value);
    } catch(...) {
        //nothing
    }

    return nullptr;
}

sp<_Uint8> _Uint8::parseOctUint8(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint8_t value = _Number::parseOctNumber(pa->getStdString());
        return createUint8(value);
    } catch(...) {
        //nothing
    }

    return nullptr;
}

sp<_Uint8> _Uint8::parseBinaryUint8(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint8_t value = _Number::parseBinaryNumber(pa->getStdString());
        return createUint8(value);
    } catch(...) {
        //nothing
    }

    return nullptr;
}

sp<_String> _Uint8::className() {
    return createString("Uint8");
}

_Uint8::~_Uint8() {
}

}
