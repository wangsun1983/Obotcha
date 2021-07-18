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
#include <algorithm>

#include "Uint32.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

_Uint32::_Uint32():val(0) {

}

_Uint32::_Uint32(uint32_t v) : val(v) {}

_Uint32::_Uint32(const Uint32 &v) {
    if(v == nullptr) {
        Trigger(InitializeException,"Object is null");
    }
    
    val = v->val;
}
    
uint32_t _Uint32::toValue() {
    return val;
}

bool _Uint32::equals(const Uint32 &p) {
    return val == p->val;
}

bool _Uint32::equals(uint32_t p) {
    return val == p;
}

bool _Uint32::equals(const _Uint32 *p) {
    return val == p->val;
}

void _Uint32::update(uint32_t v) {
    val = v;
}

void _Uint32::update(const sp<_Uint32> &v) {
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

sp<_Uint32> _Uint32::parseDecUint32(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint32_t value = _Number::parseDecNumber(pa->getStdString());
        return createUint32(value);
    } catch(const char *err){}

    return nullptr;
}

sp<_Uint32> _Uint32::parseHexUint32(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint32_t value = _Number::parseHexNumber(pa->getStdString());
        return createUint32(value);
    } catch(...) {
        //nothing
    }

    return nullptr;
}

sp<_Uint32> _Uint32::parseOctUint32(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint32_t value = _Number::parseOctNumber(pa->getStdString());
        return createUint32(value);
    } catch(...) {
        //nothing
    }

    return nullptr;
}

sp<_Uint32> _Uint32::parseBinaryUint32(const sp<_String> &v) {
    try {
        String pa = v->trimAll();
        uint32_t value = _Number::parseBinaryNumber(pa->getStdString());
        return createUint32(value);
    } catch(...) {
        //nothing
    }

    return nullptr;
}

sp<_String> _Uint32::className() {
    return createString("Uint32");
}

uint64_t _Uint32::hashcode() {
    return std::hash<uint32_t>{}(val);
}

_Uint32::~_Uint32() {
}

}
