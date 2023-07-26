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

_Uint8::_Uint8() : val(0) {}

_Uint8::_Uint8(uint8_t v) : val(v) {}

_Uint8::_Uint8(const Uint8 &v) {
    if (v == nullptr) {
        Trigger(InitializeException, "Object is null")
    }

    val = v->val;
}

uint8_t _Uint8::toValue() { return val; }

bool _Uint8::equals(Object p) { 
    auto v = dynamic_cast<_Uint8 *>(p.get_pointer());
    return v != nullptr && val == v->val;
}

bool _Uint8::sameAs(uint8_t p) { 
    return val == p; 
}

void _Uint8::update(uint8_t v) { val = v; }

void _Uint8::update(const sp<_Uint8> &v) { val = v->val; }

sp<_String> _Uint8::toHexString() {
    return createString(_Number::ToHexString(val));
}

sp<_String> _Uint8::toOctalString() {
    return createString(_Number::ToOctalString(val));
}

sp<_String> _Uint8::toBinaryString() {
    return createString(_Number::ToBinaryString(val));
}

uint64_t _Uint8::hashcode() const { 
    return std::hash<uint8_t>{}(val); 
}

sp<_String> _Uint8::toString() {
    return createString(_Number::ToDecString(val));
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
    );
    return nullptr;
}

sp<_Uint8> _Uint8::ParseHexString(const sp<_String> &v) {
    NoException(
        uint8_t value = ParseHexNumber(v->getStdString());
        return createUint8(value);
    );

    return nullptr;
}

sp<_Uint8> _Uint8::ParseOctString(const sp<_String> &v) {
    NoException(
        uint8_t value = ParseOctNumber(v->getStdString());
        return createUint8(value);
    );

    return nullptr;
}

sp<_Uint8> _Uint8::ParseBinaryString(const sp<_String> &v) {
    NoException(
        uint8_t value = ParseBinaryNumber(v->getStdString());
        return createUint8(value);
    );

    return nullptr;
}

sp<_String> _Uint8::ClassName() { 
    return createString("Uint8"); 
}

} // namespace obotcha
