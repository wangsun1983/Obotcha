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

const sp<_Boolean> _Boolean::False = createBoolean(false);

const sp<_Boolean> _Boolean::True = createBoolean(true);

const sp<_String> _Boolean::FalseString = createString("False");

const sp<_String> _Boolean::TrueString = createString("True");

_Boolean::_Boolean() : val(true) {}

_Boolean::_Boolean(bool v) : val(v) {}

_Boolean::_Boolean(const char *s) : _Boolean(createString(s)) {}

_Boolean::_Boolean(const sp<_String> str) {
    int value = _Boolean::_parse(str);
    switch (value) {
    case 1:
        this->val = true;
        return;

    case 0:
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

void _Boolean::update(const sp<_Boolean> v) { 
    val = v->val; 
}

bool _Boolean::equals(bool p) { 
    return val == p; 
}

sp<_String> _Boolean::toString() {
    if (val) {
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

uint64_t _Boolean::hashcode() { return std::hash<bool>{}(val); }

sp<_Boolean> _Boolean::parse(const sp<_String> str) {
    int value = _Boolean::_parse(str);
    switch (value) {
    case 1:
        return createBoolean(true);

    case 0:
        return createBoolean(false);
    }

    return nullptr;
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

int _Boolean::_parse(sp<_String> str) {
    String trimStr = str->trimAll();
    if(trimStr->equalsIgnoreCase("true")) {
        return 1;
    }

    if(trimStr->equalsIgnoreCase("false")) {
        return 0;
    }

    return -1;
}

_Boolean::~_Boolean() {}

} // namespace obotcha