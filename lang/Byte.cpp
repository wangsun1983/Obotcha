/**
 * @file Double.cpp
 * @brief this class used for Double
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_198３＠yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <algorithm>

#include "Byte.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "Integer.hpp"
#include "NullPointerException.hpp"

namespace obotcha {

_Byte::_Byte() : val(0) {
    //nothing
}

_Byte::_Byte(byte v) : val(v) {
    //nothing
}

_Byte::_Byte(const Byte &v) { 
    val = v->val; 
}

_Byte::_Byte(sp<_String> &v) {
    val = _Number::ParseDecNumber(v->getStdString());
}

byte _Byte::toValue() { 
    return val;
}

bool _Byte::equals(const Byte &p) { 
    return val == p->val; 
}

bool _Byte::equals(byte p) { 
    return val == p; 
}

bool _Byte::equals(const _Byte *p) { 
    return val == p->val; 
}

void _Byte::update(byte v) { 
    val = v;
}

void _Byte::update(const sp<_Byte> &v) { 
    val = v->val; 
}

uint64_t _Byte::hashcode() { 
    return std::hash<byte>{}(val); 
}

sp<_String> _Byte::toHexString() {
    Integer v = createInteger(val);
    return v->toHexString();
}

sp<_String> _Byte::toOctalString() {
    Integer v = createInteger(val);
    return v->toOctalString();
}

sp<_String> _Byte::toBinaryString() {
    Integer v = createInteger(val);
    return v->toBinaryString();
}

sp<_String> _Byte::toString() {
    Integer v = createInteger(val);
    return v->toString();
}

sp<_String> _Byte::ToString(byte i) {
    Integer v = createInteger(i);
    return v->toString();
}

sp<_Byte> _Byte::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Byte> _Byte::ParseDecString(const sp<_String> &v) {
    NoException(
        byte value = _Number::ParseDecNumber(v->getStdString());
        return createByte(value);
    );

    return nullptr;
}

sp<_Byte> _Byte::ParseHexString(const sp<_String> &v) {
    // check whether 0xaaa
    NoException(
        byte value = _Number::ParseHexNumber(v->getStdString());
        return createByte(value);
    );

    return nullptr;
}

sp<_Byte> _Byte::ParseOctString(const sp<_String> &v) {
    NoException(
        byte value = _Number::ParseOctNumber(v->getStdString());
        return createByte(value);
    );

    return nullptr;
}

sp<_Byte> _Byte::ParseBinaryString(const sp<_String> &v) {
    NoException(
        byte value = _Number::ParseBinaryNumber(v->getStdString());
        return createByte(value);
    );

    return nullptr;
}

sp<_String> _Byte::ClassName() { 
    return createString("Byte"); 
}

_Byte::~_Byte() {}

} // namespace obotcha
