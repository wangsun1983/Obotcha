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
#include "NumberTransformer.hpp"

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
    return createString(st(NumberTransformer)::ToHexString(mValue));
}

sp<_String> _Long::toOctalString() const {
    return createString(st(NumberTransformer)::ToOctalString(mValue));
}

sp<_String> _Long::toBinaryString() const {
    return createString(st(NumberTransformer)::ToBinaryString(mValue));
}

sp<_String> _Long::toString() {
    return createString(st(NumberTransformer)::ToDecString(mValue));
}

sp<_String> _Long::ToString(int v) {
    return createString(st(NumberTransformer)::ToDecString(v));
}

sp<_Long> _Long::ParseDecLong(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseDecNumber<long>(v->getStdString());
        return createLong(value);
    )

    return nullptr;
}

sp<_Long> _Long::ParseHexLong(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseHexNumber<long>(v->getStdString());
        return createLong(value);
    )

    return nullptr;
}

sp<_Long> _Long::ParseOctLong(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseOctNumber<long>(v->getStdString());
        return createLong(value);
    )

    return nullptr;
}

sp<_Long> _Long::ParseBinaryLong(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseBinaryNumber<long>(v->getStdString());
        return createLong(value);
    )
    return nullptr;
}

sp<_String> _Long::ClassName() { 
    return createString("Long"); 
}

} // namespace obotcha
