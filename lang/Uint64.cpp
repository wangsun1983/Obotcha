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
#include <algorithm>

#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "Uint64.hpp"

namespace obotcha {

_Uint64::_Uint64() : val(0) {}

_Uint64::_Uint64(uint64_t v) : val(v) {}

_Uint64::_Uint64(const Uint64 &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null");
    }

    val = v->val;
}

uint64_t _Uint64::toValue() { return val; }

bool _Uint64::equals(const Uint64 &p) { return val == p->val; }

bool _Uint64::equals(uint64_t p) { return val == p; }

bool _Uint64::equals(const _Uint64 *p) { return val == p->val; }

void _Uint64::update(uint64_t v) { val = v; }

void _Uint64::update(const sp<_Uint64> &v) { val = v->val; }

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

sp<_Uint64> _Uint64::parseDecUint64(const sp<_String> &v) {
    try {
        String pa = v->trimAll()->replaceAll("\n","")->replaceAll("\r","");
        uint64_t value = _Number::parseDecNumber(pa->getStdString());
        return createUint64(value);
    } catch (int e) {
    }

    return nullptr;
}

sp<_Uint64> _Uint64::parseHexUint64(const sp<_String> &v) {
    try {
        uint64_t value = _Number::parseHexNumber(v->getStdString());
        return createUint64(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Uint64> _Uint64::parseOctUint64(const sp<_String> &v) {
    try {
        uint64_t value = _Number::parseOctNumber(v->getStdString());
        return createUint64(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Uint64> _Uint64::parseBinaryUint64(const sp<_String> &v) {
    try {
        uint32_t value = _Number::parseBinaryNumber(v->getStdString());
        return createUint64(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_String> _Uint64::className() { return createString("Uint64"); }

uint64_t _Uint64::hashcode() { return std::hash<uint64_t>{}(val); }

_Uint64::~_Uint64() {}

} // namespace obotcha
