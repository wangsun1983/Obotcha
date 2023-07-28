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

_Long::_Long(long v) : mValue(v) {
}

_Long::_Long(const Long &v) : mValue(v->mValue) {
}

long _Long::toValue() const { 
    return mValue; 
}

bool _Long::equals(Object p) { 
    auto v = dynamic_cast<_Long *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

bool _Long::sameAs(long p) const { 
     return mValue == p; 
}

void _Long::update(long v) { 
    mValue = v; 
}

void _Long::update(const sp<_Long> &v) { 
    mValue = v->mValue; 
}

uint64_t _Long::hashcode() const { 
    return std::hash<long>{}(mValue); 
}

sp<_String> _Long::toHexString() const {
    return createString(_Number::ToHexString(mValue));
}

sp<_String> _Long::toOctalString() const {
    return createString(_Number::ToOctalString(mValue));
}

sp<_String> _Long::toBinaryString() const {
    return createString(_Number::ToBinaryString(mValue));
}

sp<_String> _Long::toString() {
    return createString(_Number::ToDecString(mValue));
}

sp<_String> _Long::ToString(int v) {
    return createString(_Number::ToDecString(v));
}

sp<_Long> _Long::ParseDecLong(const sp<_String> &v) {
    NoException(
        long value = _Number::ParseDecNumber(v->getStdString());
        return createLong(value);
    );

    return nullptr;
}

sp<_Long> _Long::ParseHexLong(const sp<_String> &v) {
    NoException(
        long value = _Number::ParseHexNumber(v->getStdString());
        return createLong(value);
    );

    return nullptr;
}

sp<_Long> _Long::ParseOctLong(const sp<_String> &v) {
    NoException(
        long value = _Number::ParseOctNumber(v->getStdString());
        return createLong(value);
    );

    return nullptr;
}

sp<_Long> _Long::ParseBinaryLong(const sp<_String> &v) {
    NoException(
        long value = _Number::ParseBinaryNumber(v->getStdString());
        return createLong(value);
    );
    return nullptr;
}

sp<_String> _Long::ClassName() { 
    return createString("Long"); 
}

} // namespace obotcha
