/**
 * @file Uint32.cpp
 * @brief this class used for uint32
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
#include "NullPointerException.hpp"
#include "Uint32.hpp"

namespace obotcha {

_Uint32::_Uint32(uint32_t v) : mValue(v) {
}

_Uint32::_Uint32(const Uint32 &v):mValue(v->mValue) {
}

uint32_t _Uint32::toValue() const { 
    return mValue; 
}

bool _Uint32::equals(Object p) { 
    auto v = dynamic_cast<_Uint32 *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

bool _Uint32::sameAs(uint32_t p) const { 
     return mValue == p; 
}

void _Uint32::update(uint32_t v) { 
    mValue = v; 
}

void _Uint32::update(const sp<_Uint32> &v) { 
    mValue = v->mValue; 
}

sp<_String> _Uint32::toHexString() const {
    return createString(_Number::ToHexString(mValue));
}

sp<_String> _Uint32::toOctalString() const {
    return createString(_Number::ToOctalString(mValue));
}

sp<_String> _Uint32::toBinaryString() const {
    return createString(_Number::ToBinaryString(mValue));
}

sp<_String> _Uint32::toString() {
    return createString(_Number::ToDecString(mValue));
}

sp<_String> _Uint32::ToString(uint32_t v) {
    return createString(_Number::ToDecString(v));
}

sp<_Uint32> _Uint32::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Uint32> _Uint32::ParseDecString(const sp<_String> &v) {
    NoException(
        uint32_t value = _Number::ParseDecNumber(v->getStdString());
        return createUint32(value);
    )

    return nullptr;
}

sp<_Uint32> _Uint32::ParseHexString(const sp<_String> &v) {
    NoException(
        uint32_t value = _Number::ParseHexNumber(v->getStdString());
        return createUint32(value);
    )

    return nullptr;
}

sp<_Uint32> _Uint32::ParseOctString(const sp<_String> &v) {
    NoException(
        uint32_t value = _Number::ParseOctNumber(v->getStdString());
        return createUint32(value);
    )

    return nullptr;
}

sp<_Uint32> _Uint32::ParseBinaryString(const sp<_String> &v) {
    NoException(
        uint32_t value = _Number::ParseBinaryNumber(v->getStdString());
        return createUint32(value);
    )

    return nullptr;
}

sp<_String> _Uint32::ClassName() { 
    return createString("Uint32");
}

uint64_t _Uint32::hashcode() const { 
    return std::hash<uint32_t>{}(mValue); 
}

} // namespace obotcha
