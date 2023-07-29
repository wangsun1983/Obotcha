/**
 * @file String.cpp
 * @brief this class used for uint8
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
#include "Uint8.hpp"

namespace obotcha {

_Uint8::_Uint8(uint8_t v) : mValue(v) {
}

_Uint8::_Uint8(const Uint8 &v):mValue(v->mValue) {
}

uint8_t _Uint8::toValue() const { 
    return mValue; 
}

bool _Uint8::equals(Object p) { 
    auto v = dynamic_cast<_Uint8 *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

bool _Uint8::sameAs(uint8_t p) const { 
    return mValue == p; 
}

void _Uint8::update(uint8_t v) { 
    mValue = v; 
}

void _Uint8::update(const sp<_Uint8> &v) { 
    mValue = v->mValue; 
}

sp<_String> _Uint8::toHexString() const {
    return createString(_Number::ToHexString(mValue));
}

sp<_String> _Uint8::toOctalString() const {
    return createString(_Number::ToOctalString(mValue));
}

sp<_String> _Uint8::toBinaryString() const {
    return createString(_Number::ToBinaryString(mValue));
}

uint64_t _Uint8::hashcode() const { 
    return std::hash<uint8_t>{}(mValue); 
}

sp<_String> _Uint8::toString() {
    return createString(_Number::ToDecString(mValue));
}

sp<_String> _Uint8::ToString(uint8_t i) {
    return createString(_Number::ToDecString(i));
}

sp<_Uint8> _Uint8::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Uint8> _Uint8::ParseDecString(const sp<_String> &v) {
    NoException(
        uint8_t value = ParseDecNumber(v->getStdString());
        return createUint8(value);
    )
    return nullptr;
}

sp<_Uint8> _Uint8::ParseHexString(const sp<_String> &v) {
    NoException(
        uint8_t value = ParseHexNumber(v->getStdString());
        return createUint8(value);
    )

    return nullptr;
}

sp<_Uint8> _Uint8::ParseOctString(const sp<_String> &v) {
    NoException(
        uint8_t value = ParseOctNumber(v->getStdString());
        return createUint8(value);
    )

    return nullptr;
}

sp<_Uint8> _Uint8::ParseBinaryString(const sp<_String> &v) {
    NoException(
        uint8_t value = ParseBinaryNumber(v->getStdString());
        return createUint8(value);
    )

    return nullptr;
}

sp<_String> _Uint8::ClassName() { 
    return createString("Uint8"); 
}

} // namespace obotcha
