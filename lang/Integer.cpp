/**
 * @file Integer.cpp
 * @brief this class used for int
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <algorithm>
#include <bitset>
#include <math.h>
#include <memory.h>
#include <sstream>
#include <stdio.h>

#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "Integer.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

const int _Integer::MAX_VALUE = 0x7fffffff;

const int _Integer::MIN_VALUE = 0x80000000;

_Integer::_Integer() : val(0) {}

_Integer::_Integer(int v) : val(v) {}

_Integer::_Integer(const Integer &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null");
    }

    val = v->toValue();
}

int _Integer::toValue() { return val; }

bool _Integer::equals(const Integer &p) { return val == p->val; }

uint64_t _Integer::hashcode() { return std::hash<int>{}(val); }

bool _Integer::equals(int p) { return val == p; }

bool _Integer::equals(const _Integer *p) { return val == p->val; }

void _Integer::update(int v) { val = v; }

void _Integer::update(const sp<_Integer> &v) { val = v->val; }

// 16
sp<_String> _Integer::toHexString() {
    return createString(_Number::toHexString(val));
}

// 10
sp<_String> _Integer::toString() {
    return createString(_Number::toDecString(val));
}

// 8
sp<_String> _Integer::toOctalString() {
    return createString(_Number::toOctalString(val));
}

// 2
sp<_String> _Integer::toBinaryString() {
    return createString(_Number::toBinaryString(val));
}

sp<_String> _Integer::toString(int i) {
    return createString(_Number::toDecString(i));
}

Integer _Integer::parseDecInt(const sp<_String> &v) {
    try {
        String pa = v->trimAll()->replaceAll(std::string("\n"),"")->replaceAll("\r","");
        int value = _Number::parseDecNumber(pa->getStdString());
        return createInteger(value);
    } catch (...) {
    }

    return nullptr;
}

Integer _Integer::parseHexInt(const sp<_String> &v) {
    try {
        String pa = v->trimAll()->replaceAll(std::string("\n"),"")->replaceAll("\r","");
        int value = _Number::parseHexNumber(pa->getStdString());
        return createInteger(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

Integer _Integer::parseOctInt(const sp<_String> &v) {
    try {
        String pa = v->trimAll()->replaceAll(std::string("\n"),"")->replaceAll("\r","");
        int value = _Number::parseOctNumber(pa->getStdString());
        return createInteger(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

Integer _Integer::parseBinaryInt(const sp<_String> &v) {
    try {
        String pa = v->trimAll()->replaceAll(std::string("\n"),"")->replaceAll("\r","");
        int value = _Number::parseBinaryNumber(pa->getStdString());
        return createInteger(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

String _Integer::className() { return createString("Integer"); }

_Integer::~_Integer() {}

} // namespace obotcha