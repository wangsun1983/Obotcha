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
#include "Byte.hpp"
#include "Integer.hpp"
#include "NumberTransformer.hpp"
#include "String.hpp"

namespace obotcha {

_Byte::_Byte() : mValue(0) {
}

_Byte::_Byte(byte v) : mValue(v) {
}

_Byte::_Byte(const Byte &v):mValue(v->mValue) { 
}

_Byte::_Byte(const sp<_String> &v) {
    mValue = st(NumberTransformer)::ParseDecNumber<byte>(v->getStdString());
}

byte _Byte::toValue() const { 
    return mValue;
}

bool _Byte::equals(Object p) { 
    auto v = dynamic_cast<_Byte *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

bool _Byte::sameAs(byte v) const {
    return mValue == v;
}

void _Byte::update(byte v) { 
    mValue = v;
}

void _Byte::update(const sp<_Byte> &v) { 
    mValue = v->mValue; 
}

uint64_t _Byte::hashcode() const { 
    return std::hash<byte>{}(mValue); 
}

sp<_String> _Byte::toHexString() const {
    return createInteger(mValue)->toHexString();
}

sp<_String> _Byte::toOctalString() const {
    return createInteger(mValue)->toOctalString();
}

sp<_String> _Byte::toBinaryString() const {
    return createInteger(mValue)->toBinaryString();
}

sp<_String> _Byte::toString() {
    return createInteger(mValue)->toString();
}

sp<_String> _Byte::ToString(byte v) {
    return createInteger(v)->toString();
}

sp<_Byte> _Byte::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Byte> _Byte::ParseDecString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseDecNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Byte> _Byte::ParseHexString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseHexNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Byte> _Byte::ParseOctString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseOctNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Byte> _Byte::ParseBinaryString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseBinaryNumber<byte>(v->getStdString());
        return createByte(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_String> _Byte::ClassName() { 
    return createString("Byte"); 
}

} // namespace obotcha
