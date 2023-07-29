/**
 * @file Uint16.cpp
 * @brief this class used for uint16
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
#include "Number.hpp"
#include "Uint16.hpp"

namespace obotcha {

_Uint16::_Uint16(uint16_t v) : mValue(v) {
}

_Uint16::_Uint16(const Uint16 &v):mValue(v->mValue) {
}

uint16_t _Uint16::toValue() const { 
    return mValue; 
}

bool _Uint16::equals(Object p) { 
    auto v = dynamic_cast<_Uint16 *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

bool _Uint16::sameAs(uint16_t p) const { 
     return mValue == p; 
}

void _Uint16::update(uint16_t v) { 
    mValue = v;
}

void _Uint16::update(const sp<_Uint16> &v) { 
    mValue = v->mValue; 
}

sp<_String> _Uint16::toHexString() const {
    return createString(_Number::ToHexString(mValue));
}

sp<_String> _Uint16::toOctalString() const {
    return createString(_Number::ToOctalString(mValue));
}

sp<_String> _Uint16::toBinaryString() const {
    return createString(_Number::ToBinaryString(mValue));
}

sp<_String> _Uint16::toString() {
    return createString(_Number::ToDecString(mValue));
}

sp<_String> _Uint16::ToString(uint16_t i) {
    return createString(_Number::ToDecString(i));
}

sp<_Uint16> _Uint16::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Uint16> _Uint16::ParseDecString(const sp<_String> &v) {
    NoException(
        uint16_t value = _Number::ParseDecNumber(v->getStdString());
        return createUint16(value);
    )

    return nullptr;
}

sp<_Uint16> _Uint16::ParseHexString(const sp<_String> &v) {
    NoException(
        uint16_t value = _Number::ParseHexNumber(v->getStdString());
        return createUint16(value);
    )

    return nullptr;
}

sp<_Uint16> _Uint16::ParseOctString(const sp<_String> &v) {
    NoException(
        uint16_t value = _Number::ParseOctNumber(v->getStdString());
        return createUint16(value);
    )

    return nullptr;
}

sp<_Uint16> _Uint16::ParseBinaryString(const sp<_String> &v) {
    NoException(
        uint16_t value = _Number::ParseBinaryNumber(v->getStdString());
        return createUint16(value);
    )

    return nullptr;
}

sp<_String> _Uint16::ClassName() { 
    return createString("Uint16"); 
}

uint64_t _Uint16::hashcode() const { 
    return std::hash<uint16_t>{}(mValue); 
}

} // namespace obotcha
