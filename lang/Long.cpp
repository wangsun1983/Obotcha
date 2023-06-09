/**
 * @file Long.cpp
 * @brief this class used for long
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
#include "Long.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

_Long::_Long() : val(0) {}

_Long::_Long(long v) : val(v) {}

_Long::_Long(const Long &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null");
    }

    val = v->val;
}

long _Long::toValue() { return val; }

bool _Long::equals(const Long &p) { return val == p->val; }

bool _Long::equals(long p) { return val == p; }

bool _Long::equals(const _Long *p) { return val == p->val; }

void _Long::update(long v) { val = v; }

void _Long::update(const sp<_Long> &v) { val = v->val; }

uint64_t _Long::hashcode() { return std::hash<long>{}(val); }

sp<_String> _Long::toHexString() {
    return createString(_Number::ToHexString(val));
}

sp<_String> _Long::toOctalString() {
    return createString(_Number::ToOctalString(val));
}

sp<_String> _Long::toBinaryString() {
    return createString(_Number::ToBinaryString(val));
}

sp<_String> _Long::toString() {
    return createString(_Number::ToDecString(val));
}

sp<_String> _Long::toString(int i) {
    return createString(_Number::ToDecString(i));
}

sp<_Long> _Long::ParseDecLong(const sp<_String> &v) {
    try {
        long value = _Number::ParseDecNumber(v->getStdString());
        return createLong(value);
    } catch (...) {
    }

    return nullptr;
}

sp<_Long> _Long::ParseHexLong(const sp<_String> &v) {
    try {
        long value = _Number::ParseHexNumber(v->getStdString());
        return createLong(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Long> _Long::ParseOctLong(const sp<_String> &v) {
    try {
        long value = _Number::ParseOctNumber(v->getStdString());
        return createLong(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_Long> _Long::ParseBinaryLong(const sp<_String> &v) {
    try {
        long value = _Number::ParseBinaryNumber(v->getStdString());
        return createLong(value);
    } catch (...) {
        // nothing
    }

    return nullptr;
}

sp<_String> _Long::className() { return createString("Long"); }

_Long::~_Long() {}

} // namespace obotcha
