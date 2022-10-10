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

#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "Uint32.hpp"

namespace obotcha {

_Uint32::_Uint32() : val(0) {}

_Uint32::_Uint32(uint32_t v) : val(v) {}

_Uint32::_Uint32(const Uint32 &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null");
    }

    val = v->val;
}

uint32_t _Uint32::toValue() { return val; }

bool _Uint32::equals(const Uint32 &p) { return val == p->val; }

bool _Uint32::equals(uint32_t p) { return val == p; }

bool _Uint32::equals(const _Uint32 *p) { return val == p->val; }

void _Uint32::update(uint32_t v) { val = v; }

void _Uint32::update(const sp<_Uint32> &v) { val = v->val; }

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

sp<_Uint32> _Uint32::parse(const sp<_String> &v) {
    return parseDecString(v);
}

sp<_Uint32> _Uint32::parseDecString(const sp<_String> &v) {
    try {
        uint32_t value = _Number::parseDecNumber(v->getStdString());
        return createUint32(value);
    } catch (int e) {
    }

    return nullptr;
}

sp<_Uint32> _Uint32::parseHexString(const sp<_String> &v) {
    try {
        uint32_t value = _Number::parseHexNumber(v->getStdString());
        return createUint32(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Uint32> _Uint32::parseOctString(const sp<_String> &v) {
    try {
        uint32_t value = _Number::parseOctNumber(v->getStdString());
        return createUint32(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Uint32> _Uint32::parseBinaryString(const sp<_String> &v) {
    try {
        uint32_t value = _Number::parseBinaryNumber(v->getStdString());
        return createUint32(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_String> _Uint32::className() { return createString("Uint32"); }

uint64_t _Uint32::hashcode() { return std::hash<uint32_t>{}(val); }

_Uint32::~_Uint32() {}

} // namespace obotcha
