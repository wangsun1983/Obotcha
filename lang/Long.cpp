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

#include "Long.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

_Long::_Long(long v) : val(v) {}

_Long::_Long(Long &v) {
    if(v == nullptr) {
        throwInitializeException("Object is null");
    }
    
    val = v->val;
}
    
long _Long::toValue() {
    return val;
}

bool _Long::equals(Long &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Long::equals(long p) {
    return val == p;
}

bool _Long::equals(const _Long *p) {
    if(p == nullptr) {
        throwNullPointerException("Long parserInt nullptr");
    }

    return val == p->val;
}

void _Long::update(long v) {
    val = v;
}

void _Long::update(sp<_Long> v) {
    if(v == nullptr) {
        throwNullPointerException("Long update nullptr");
    }

    val = v->val;
}

sp<_String> _Long::toHexString() {
    return createString(_Number::toHexString(val));
}

sp<_String> _Long::toOctalString() {
    return createString(_Number::toOctalString(val));
}

sp<_String> _Long::toBinaryString() {
    return createString(_Number::toBinaryString(val));
}

sp<_String> _Long::toString() {
    return createString(_Number::toDecString(val));
}

sp<_String> _Long::toString(int i) {
    return createString(_Number::toDecString(i));
}

long _Long::parseDecLong(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("Long parserInt nullptr");
    }

    return _Number::parseDecNumber(v->getStdString());
}

long _Long::parseHexLong(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("parseHexLong nullptr");
    }
    
    return _Number::parseHexNumber(v->getStdString());
}

long _Long::parseOctLong(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("parseOctLong nullptr");
    }
    
    return _Number::parseOctNumber(v->getStdString());
}

long _Long::parseBinaryLong(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("parseBinaryLong nullptr");
    }
    
    return _Number::parseBinaryNumber(v->getStdString());
}

_Long::~_Long() {
}

}