/**
 * @file Boolean.cpp
 * @brief this class used for Boolean
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <algorithm>

#include "Boolean.hpp"
#include "InitializeException.hpp"
#include "IllegalArgumentException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

const sp<_Boolean> _Boolean::False = createBoolean(false);

const sp<_Boolean> _Boolean::True = createBoolean(true);

const sp<_String> _Boolean::FalseString = createString("False");

const sp<_String> _Boolean::TrueString = createString("True");

_Boolean::_Boolean():val(true) {}

_Boolean::_Boolean(bool v) : val(v) {

}

_Boolean::_Boolean(const char * s):_Boolean(createString(s)) {

}

_Boolean::_Boolean(const sp<_String> str) {
    String trimStr = str->trimAll();
    const char *data = trimStr->toChars();
    
    if((trimStr->size() == 4) &&
        (data[0] == 't' || data[0] == 'T')
        &&(data[1] == 'r' || data[1] == 'R')
        &&(data[2] == 'u' || data[2] == 'U')
        &&(data[3] == 'e' || data[3] == 'E')) {
        val = true;
        return;
    }

    if((trimStr->size() == 5) &&
        (data[0] == 'f' || data[0] == 'F')
        &&(data[1] == 'a' || data[1] == 'A')
        &&(data[2] == 'l' || data[2] == 'L')
        &&(data[3] == 's' || data[3] == 'S')
        &&(data[4] == 'e' || data[4] == 'E')) {
        val = false;
        return;
    }

    Trigger(InitializeException,"Boolean init failed");
}

_Boolean::_Boolean(const Boolean &v) {
    if(v == nullptr) {
        Trigger(NullPointerException,"Object is null");
    }
    
    val = v->val;
}
    
bool _Boolean::toValue() {
    return val;
}

bool _Boolean::equals(const Boolean &p) {
    return val == p->val;
}

bool _Boolean::equals(const _Boolean *p) {
    return val == p->val;
}

void _Boolean::update(bool v) {
    val = v;
}

void _Boolean::update(const sp<_Boolean> v) {
    val = v->val;
}

bool _Boolean::equals(bool p) {
    return val == p;
}

sp<_String> _Boolean::toString() {
    if(val) {
        return TrueString;
    }

    return FalseString;
}

bool _Boolean::logicOr(bool v) {
    val |= v;

    return val;
}

bool _Boolean::logicOr(const sp<_Boolean> v) {
    val |= v->toValue();

    return val;
}

bool _Boolean::logicAnd(bool v) {
    val &= v;

    return val;
}

bool _Boolean::logicAnd(const sp<_Boolean> v) {
    val &= v->toValue();

    return val;
}

uint64_t _Boolean::hashcode() {
    return std::hash<bool>{}(val);
}

sp<_Boolean> _Boolean::parse(const sp<_String> v) {
    return createBoolean(v);
}

sp<_Boolean> _Boolean::parse(const char *v) {
    return parse(createString(v));
}

sp<_Boolean> _Boolean::parse(bool v) {
    return createBoolean(v);
}

sp<_String> _Boolean::className() {
    return createString("Boolean");
}

_Boolean::~_Boolean() {
}

}