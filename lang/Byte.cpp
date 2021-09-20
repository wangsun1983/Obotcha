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
#include <algorithm>

#include "Byte.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "Integer.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

_Byte::_Byte() : val(0) {}

_Byte::_Byte(byte v) : val(v) {}

_Byte::_Byte(const Byte &v) { val = v->val; }

byte _Byte::toValue() { return val; }

bool _Byte::equals(const Byte &p) { return val == p->val; }

bool _Byte::equals(byte p) { return val == p; }

bool _Byte::equals(const _Byte *p) { return val == p->val; }

void _Byte::update(byte v) { val = v; }

void _Byte::update(const sp<_Byte> v) { val = v->val; }

uint64_t _Byte::hashcode() { return std::hash<byte>{}(val); }

sp<_String> _Byte::toHexString() {
    Integer v = createInteger(val);
    return v->toHexString();
}

sp<_String> _Byte::toOctalString() {
    Integer v = createInteger(val);
    return v->toOctalString();
}

sp<_String> _Byte::toBinaryString() {
    Integer v = createInteger(val);
    return v->toBinaryString();
}

sp<_String> _Byte::toString() {
    Integer v = createInteger(val);
    return v->toString();
}

sp<_String> _Byte::toString(byte i) {
    Integer v = createInteger(i);
    return v->toString();
}

sp<_Byte> _Byte::parseDecByte(const sp<_String> v) {
    try {
        String pa = v->trimAll();
        int value = _Number::parseDecNumber(pa->getStdString());
        return createByte(value);
    } catch (int e) {
    }

    return nullptr;
}

sp<_Byte> _Byte::parseHexByte(const sp<_String> v) {
    // check whether 0xaaa
    try {
        String pa = v->trimAll();
        int value = _Number::parseHexNumber(pa->getStdString());
        return createByte(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Byte> _Byte::parseOctByte(const sp<_String> v) {
    try {
        String pa = v->trimAll();
        int value = _Number::parseOctNumber(pa->getStdString());
        return createByte(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Byte> _Byte::parseBinaryByte(const sp<_String> v) {
    try {
        String pa = v->trimAll();
        int value = _Number::parseBinaryNumber(pa->getStdString());
        return createByte(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_String> _Byte::className() { return createString("Byte"); }

_Byte::~_Byte() {}

} // namespace obotcha