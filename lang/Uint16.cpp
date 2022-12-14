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
#include <algorithm>

#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "Number.hpp"
#include "Uint16.hpp"

namespace obotcha {

_Uint16::_Uint16() : val(0) {}

_Uint16::_Uint16(uint16_t v) : val(v) {}

_Uint16::_Uint16(const Uint16 &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null");
    }

    val = v->val;
}

uint16_t _Uint16::toValue() { return val; }

bool _Uint16::equals(const Uint16 &p) { return val == p->val; }

bool _Uint16::equals(uint16_t p) { return val == p; }

bool _Uint16::equals(const _Uint16 *p) { return val == p->val; }

void _Uint16::update(uint16_t v) { val = v; }

void _Uint16::update(const sp<_Uint16> &v) { val = v->val; }

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

sp<_Uint16> _Uint16::parse(const sp<_String> &v) {
    return parseDecString(v);
}

sp<_Uint16> _Uint16::parseDecString(const sp<_String> &v) {
    try {
        uint16_t value = _Number::parseDecNumber(v->getStdString());
        return createUint16(value);
    } catch (...) {
    }

    return nullptr;
}

sp<_Uint16> _Uint16::parseHexString(const sp<_String> &v) {
    try {
        uint16_t value = _Number::parseHexNumber(v->getStdString());
        return createUint16(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Uint16> _Uint16::parseOctString(const sp<_String> &v) {
    try {
        uint16_t value = _Number::parseOctNumber(v->getStdString());
        return createUint16(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Uint16> _Uint16::parseBinaryString(const sp<_String> &v) {
    try {
        uint16_t value = _Number::parseBinaryNumber(v->getStdString());
        return createUint16(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_String> _Uint16::className() { return createString("Uint16"); }

uint64_t _Uint16::hashcode() { return std::hash<uint16_t>{}(val); }

_Uint16::~_Uint16() {}

} // namespace obotcha
