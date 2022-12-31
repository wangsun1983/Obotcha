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
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

#define __VAL_TRUE__ 0
#define __VAL_FALSE__ 1    
#define __VAL_INVALID__ -1

#define __STRING_FALSE__ "false"
#define __STRING_TRUE__ "true"

_Boolean::_Boolean() : val(true) {
    //nothing
}

_Boolean::_Boolean(bool v) : val(v) {
    //nothing
}

_Boolean::_Boolean(const char *s) : _Boolean(createString(s)) {
    //nothing
}

_Boolean::_Boolean(const sp<_String> str) {
    int value = _Boolean::_parse(str);
    switch (value) {
    case __VAL_TRUE__:
        this->val = true;
        return;

    case __VAL_FALSE__:
        this->val = false;
        return;
    }
    Trigger(InitializeException, "init failed");
}

_Boolean::_Boolean(const Boolean &v) {
    if (v == nullptr) {
        Trigger(NullPointerException, "Object is null");
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

void _Boolean::update(const sp<_Boolean> &v) {
    val = v->val;
}

bool _Boolean::equals(bool p) {
    return val == p;
}

sp<_String> _Boolean::toString() {
    return val?createString(__STRING_TRUE__):createString(__STRING_FALSE__);
}

bool _Boolean::logicOr(bool v) {
    val |= v;
    return val;
}

bool _Boolean::logicOr(const sp<_Boolean> &v) {
    val |= v->toValue();
    return val;
}

bool _Boolean::logicAnd(bool v) {
    val &= v;
    return val;
}

bool _Boolean::logicAnd(const sp<_Boolean> &v) {
    val &= v->toValue();
    return val;
}

bool _Boolean::logicXor(bool v) {
    val = val ^ v;
    return val;
}

bool _Boolean::logicXor(const sp<_Boolean>&v) {
    val = val ^ v->toValue();
    return val;   
}


uint64_t _Boolean::hashcode() { 
    return val?2097 : 144;
}

sp<_Boolean> _Boolean::parse(const sp<_String> &str) {
    if(str == nullptr) {
        Trigger(NullPointerException, "Parse String is null");
    }

    int value = _Boolean::_parse(str);
    switch (value) {
        case __VAL_TRUE__:
            return createBoolean(true);

        case __VAL_FALSE__:
            return createBoolean(false);
    }

    return nullptr;
}

sp<_Boolean> _Boolean::parse(const char *v) {
    return parse(createString(v));
}

sp<_String> _Boolean::className() {
    return createString("Boolean");
}

int _Boolean::_parse(sp<_String> str) {
    String trimStr = str->trimAll();
    if(trimStr->equalsIgnoreCase(__STRING_TRUE__)) {
        return __VAL_TRUE__;
    }

    if(trimStr->equalsIgnoreCase(__STRING_FALSE__)) {
        return __VAL_FALSE__;
    }

    return __VAL_INVALID__;
}

_Boolean::~_Boolean() {}

} // namespace obotcha
