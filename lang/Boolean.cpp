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

#include "Boolean.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

sp<_Boolean> _Boolean::FALSE = createBoolean(false);

sp<_Boolean> _Boolean::TRUE = createBoolean(true);

sp<_String> _Boolean::FALSE_STRING = createString("False");

sp<_String> _Boolean::TRUE_STRING = createString("True");
    
_Boolean::_Boolean(bool v) : val(v) {

}

_Boolean::_Boolean(Boolean &v) {
    if(v == nullptr) {
        throw InitializeException("Object is null");
    }
    
    val = v->val;
}
    
bool _Boolean::toValue() {
    return val;
}

bool _Boolean::equals(Boolean &p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

bool _Boolean::equals(const _Boolean *p) {
    if(p == nullptr) {
        return false;
    }

    return val == p->val;
}

void _Boolean::update(bool v) {
    val = v;
}

bool _Boolean::equals(bool p) {
    return val == p;
}

sp<_String> _Boolean::toString() {
    if(val) {
        return TRUE_STRING;
    }

    return FALSE_STRING;
}

bool _Boolean::compareTo(sp<_Boolean> v) {
    if(v == nullptr) {
        throw NullPointerException("compareTo is nullptr");
    }

    return val == v->toValue();
}

void _Boolean::logicOr(bool v) {
    val |= v;
}

void _Boolean::logicOr(sp<_Boolean> v) {
    if(v == nullptr) {
        throw NullPointerException("logicOr is nullptr");
    }

    val |= v->toValue();
}

void _Boolean::logicAnd(bool v) {
    val &= v;
}

void _Boolean::logicAnd(sp<_Boolean> v) {
    if(v == nullptr) {
        throw NullPointerException("logicOr is nullptr");
    }

    val &= v->toValue();
}

void _Boolean::logicXor(bool v) {
    val ^= v;
}

void _Boolean::logicXor(sp<_Boolean> v) {
    if(v == nullptr) {
        throw NullPointerException("logicXor is nullptr");
    }
    
    val ^= v->toValue();
}

sp<_Boolean> _Boolean::valueOf(sp<_String> v) {
    if(v == nullptr) {
        throw NullPointerException("valueOf is nullptr");
    }

    if(v->equalsIgnoreCase("true")) {
        return createBoolean(true);
    }

    return createBoolean(false);
}

sp<_Boolean> _Boolean::valueOf(char *v) {
    return valueOf(createString(v));
}

sp<_Boolean> _Boolean::valueOf(bool v) {
    return createBoolean(v);
}

_Boolean::~_Boolean() {
}

}