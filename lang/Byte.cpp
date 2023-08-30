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
#include "Integer.hpp"
#include "NumberTransformer.hpp"
#include "String.hpp"

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

_Byte::_Byte(const sp<_String> &v) {
    val = st(NumberTransformer)::ParseDecNumber<byte>(v->getStdString());
}

byte _Byte::toValue() const { 
    return val;
}

bool _Byte::equals(Object p) { 
    auto v = dynamic_cast<_Byte *>(p.get_pointer());
    return v != nullptr && val == v->val;
}

bool _Byte::sameAs(byte v) const {
    return val == v;
}

void _Byte::update(byte v) { 
    val = v;
}

void _Byte::update(const sp<_Byte> &v) { 
    val = v->val; 
}

uint64_t _Byte::hashcode() const { 
    return std::hash<byte>{}(val); 
}

sp<_String> _Byte::toHexString() const {
    return createInteger(val)->toHexString();
}

sp<_String> _Byte::toOctalString() const {
    return createInteger(val)->toOctalString();
}

sp<_String> _Byte::toBinaryString() const {
    return createInteger(val)->toBinaryString();
}

sp<_String> _Byte::toString() {
    return createInteger(val)->toString();
}

sp<_String> _Byte::ToString(byte i) {
    return createInteger(i)->toString();
}

sp<_Byte> _Byte::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Byte> _Byte::ParseDecString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseDecNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {}

    return nullptr;
}

sp<_Byte> _Byte::ParseHexString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseHexNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {}

    return nullptr;
}

sp<_Byte> _Byte::ParseOctString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseOctNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {}

    return nullptr;
}

sp<_Byte> _Byte::ParseBinaryString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseBinaryNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {}

    return nullptr;
}

sp<_String> _Byte::ClassName() { 
    return createString("Byte"); 
}

} // namespace obotcha
