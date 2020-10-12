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

#include <stdio.h>
#include <memory.h>
#include <sstream>
#include <bitset>
#include <math.h>

#include "Integer.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_Integer::_Integer(int v) : val(v) {

}

_Integer::_Integer(Integer &v) {
    if(v == nullptr) {
        throwInitializeException("Object is null");
    }

    val = v->toValue();
}

int _Integer::toValue() {
    return val;
}

bool _Integer::equals(Integer &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Integer::equals(int p) {
    return val == p;
}

bool _Integer::equals(const _Integer *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

void _Integer::update(int v) {
    val = v;
}

void _Integer::update(sp<_Integer> v) {
    if(v == nullptr) {
        throwNullPointerException("integer update null");
    }

    val = v->val;
}

sp<_String> _Integer::toHexString() {
    return createString(_Number::toHexString(val));
}

sp<_String> _Integer::toOctalString() {
    return createString(_Number::toOctalString(val));
}

sp<_String> _Integer::toBinaryString() {
    return createString(_Number::toBinaryString(val));
}

sp<_String> _Integer::toString() {
    return createString(_Number::toDecString(val));
}

sp<_String> _Integer::toString(int i) {
    return createString(_Number::toDecString(i));
}

int _Integer::parseDecInt(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("Integer parserInt nullptr");
    }

    return _Number::parseDecNumber(v->getStdString());
}

int _Integer::parseHexInt(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("parseHexInt nullptr");
    }
    
    return _Number::parseHexNumber(v->getStdString());
}

int _Integer::parseOctInt(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("parseHexInt nullptr");
    }
    
    return _Number::parseOctNumber(v->getStdString());
}

int _Integer::parseBinaryInt(sp<_String> v) {
    if(v == nullptr) {
        throwNullPointerException("parseHexInt nullptr");
    }
    
    return _Number::parseBinaryNumber(v->getStdString());
}

_Integer::~_Integer() {

}



}