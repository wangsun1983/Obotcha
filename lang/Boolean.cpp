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
#include "TransformException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

const char *_Boolean::kTrueString = "true";
const char *_Boolean::kFalseString = "false";

_Boolean::_Boolean() : mValue(true) {
}

_Boolean::_Boolean(bool v) : mValue(v) {
}

_Boolean::_Boolean(const char *s) : _Boolean(String::New(s)) {
}

_Boolean::_Boolean(const sp<_String> str) {
    try {
        this->mValue = _parse(str);
    } catch(TransformException &) {
        Trigger(InitializeException,"fail to init boolean")
    }    
}

_Boolean::_Boolean(const Boolean &v) {
    Panic(v == nullptr,NullPointerException, "Object is null")
    mValue = v->mValue;
}

bool _Boolean::toValue() const {
    return mValue;
}

bool _Boolean::equals(Object p) {
    auto v = dynamic_cast<_Boolean *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

bool _Boolean::sameAs(bool v) const {
    return mValue == v;
}

void _Boolean::update(bool v) {
    mValue = v;
}

void _Boolean::update(const sp<_Boolean> &v) {
    mValue = v->mValue;
}

sp<_String> _Boolean::toString() {
    return mValue?String::New(kTrueString):String::New(kFalseString);
}

bool _Boolean::logicOr(bool v) {
    mValue |= v;
    return mValue;
}

bool _Boolean::logicOr(const sp<_Boolean> &v) {
    mValue |= v->toValue();
    return mValue;
}

bool _Boolean::logicAnd(bool v) {
    mValue &= v;
    return mValue;
}

bool _Boolean::logicAnd(const sp<_Boolean> &v) {
    mValue &= v->toValue();
    return mValue;
}

uint64_t _Boolean::hashcode() const { 
    return mValue?2097 : 144;
}

sp<_Boolean> _Boolean::Parse(const sp<_String> &str) {
    Panic(str == nullptr,NullPointerException, "Parse String is null")
    try {
        return Boolean::New(_parse(str));
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Boolean> _Boolean::Parse(const char *v) {
    return Parse(String::New(v));
}

sp<_String> _Boolean::ClassName() {
    return String::New("Boolean");
}

bool _Boolean::_parse(sp<_String> str) {
    String trimStr = str->trimAll();
    if(trimStr->equalsIgnoreCase(kTrueString)) {
        return true;
    }

    if(trimStr->equalsIgnoreCase(kFalseString)) {
        return false;
    }

    Trigger(TransformException,"unknow string")
}

} // namespace obotcha
