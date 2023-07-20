/**
 * @file Uint64.cpp
 * @brief this class used for uint64
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
#include "Uint64.hpp"

namespace obotcha {

_Uint64::_Uint64() : val(0) {
}

_Uint64::_Uint64(uint64_t v) : val(v) {
}

_Uint64::_Uint64(const Uint64 &v) {
    Panic(v == nullptr,InitializeException, "Object is null");
    val = v->val;
}

uint64_t _Uint64::toValue() { 
    return val; 
}

bool _Uint64::equals(const Uint64 &p) { 
    return val == p->val; 
}

bool _Uint64::equals(uint64_t p) { 
    return val == p; 
}

bool _Uint64::equals(const _Uint64 *p) { 
    return val == p->val; 
}

void _Uint64::update(uint64_t v) { 
    val = v; 
}

void _Uint64::update(const sp<_Uint64> &v) { 
    val = v->val; 
}

sp<_String> _Uint64::toHexString() {
    return createString(_Number::ToHexString(val));
}

sp<_String> _Uint64::toOctalString() {
    return createString(_Number::ToOctalString(val));
}

sp<_String> _Uint64::toBinaryString() {
    return createString(_Number::ToBinaryString(val));
}

sp<_String> _Uint64::toString() {
    return createString(_Number::ToDecString(val));
}

sp<_String> _Uint64::ToString(uint64_t i) {
    return createString(_Number::ToDecString(i));
}

sp<_Uint64> _Uint64::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Uint64> _Uint64::ParseDecString(const sp<_String> &v) {
    NoException(
        uint64_t value = _Number::ParseDecNumber(v->getStdString());
        return createUint64(value);
    );
    return nullptr;
}

sp<_Uint64> _Uint64::ParseHexString(const sp<_String> &v) {
    NoException(
        uint64_t value = _Number::ParseHexNumber(v->getStdString());
        return createUint64(value);
    );

    return nullptr;
}

sp<_Uint64> _Uint64::ParseOctString(const sp<_String> &v) {
    NoException(
        uint64_t value = _Number::ParseOctNumber(v->getStdString());
        return createUint64(value);
    );

    return nullptr;
}

sp<_Uint64> _Uint64::ParseBinaryString(const sp<_String> &v) {
    NoException(
        uint32_t value = _Number::ParseBinaryNumber(v->getStdString());
        return createUint64(value);
    );

    return nullptr;
}

sp<_String> _Uint64::ClassName() { 
    return createString("Uint64"); 
}

uint64_t _Uint64::hashcode() { 
    return std::hash<uint64_t>{}(val); 
}

} // namespace obotcha
