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
#include "OStdInstanceOf.hpp"
#include "String.hpp"

namespace obotcha {

const int _Boolean::kTrueValue = 0;
const int _Boolean::kFalseValue = 1;
const int _Boolean::kInValidValue = -1;

const char *_Boolean::kTrueString = "true";
const char *_Boolean::kFalseString = "false";

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
    switch (_Boolean::_parse(str)) {
        case kTrueValue:
            this->val = true;
            return;

        case kFalseValue:
            this->val = false;
            return;
        
        default:
            Trigger(InitializeException, "init failed")
    }
}

_Boolean::_Boolean(const Boolean &v) {
    Panic(v == nullptr,NullPointerException, "Object is null")
    val = v->val;
}

bool _Boolean::toValue() const {
    return val;
}

bool _Boolean::equals(Object p) {
    auto v = dynamic_cast<_Boolean *>(p.get_pointer());
    return v != nullptr && val == v->val;
}

bool _Boolean::sameAs(bool v) const {
    return val == v;
}

void _Boolean::update(bool v) {
    val = v;
}

void _Boolean::update(const sp<_Boolean> &v) {
    val = v->val;
}

sp<_String> _Boolean::toString() {
    return val?createString(kTrueString):createString(kFalseString);
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


uint64_t _Boolean::hashcode() const { 
    return val?2097 : 144;
}

sp<_Boolean> _Boolean::Parse(const sp<_String> &str) {
    Panic(str == nullptr,NullPointerException, "Parse String is null")
    switch (_Boolean::_parse(str)) {
        case kTrueValue:
            return createBoolean(true);

        case kFalseValue:
            return createBoolean(false);

        default:
            return nullptr;
    }
}

sp<_Boolean> _Boolean::Parse(const char *v) {
    return Parse(createString(v));
}

sp<_String> _Boolean::ClassName() {
    return createString("Boolean");
}

int _Boolean::_parse(sp<_String> str) {
    String trimStr = str->trimAll();
    if(trimStr->equalsIgnoreCase(kTrueString)) {
        return kTrueValue;
    }

    if(trimStr->equalsIgnoreCase(kFalseString)) {
        return kFalseValue;
    }

    return kInValidValue;
}

} // namespace obotcha
