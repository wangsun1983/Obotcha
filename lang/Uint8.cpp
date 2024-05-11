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
#include "NumberTransformer.hpp"
#include "Uint8.hpp"
#include "String.hpp"

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
    return String::New(st(NumberTransformer)::ToHexString(mValue));
}

sp<_String> _Uint8::toOctalString() const {
    return String::New(st(NumberTransformer)::ToOctalString(mValue));
}

sp<_String> _Uint8::toBinaryString() const {
    return String::New(st(NumberTransformer)::ToBinaryString(mValue));
}

uint64_t _Uint8::hashcode() const { 
    return std::hash<uint8_t>{}(mValue); 
}

sp<_String> _Uint8::toString() {
    return String::New(st(NumberTransformer)::ToDecString(mValue));
}

sp<_String> _Uint8::ToString(uint8_t i) {
    return String::New(st(NumberTransformer)::ToDecString(i));
}

sp<_Uint8> _Uint8::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Uint8> _Uint8::ParseDecString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseDecNumber<uint8_t>(v->getStdString());
        return Uint8::New(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Uint8> _Uint8::ParseHexString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseHexNumber<uint8_t>(v->getStdString());
        return Uint8::New(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Uint8> _Uint8::ParseOctString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseOctNumber<uint8_t>(v->getStdString());
        return Uint8::New(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Uint8> _Uint8::ParseBinaryString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseBinaryNumber<uint8_t>(v->getStdString());
        return Uint8::New(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_String> _Uint8::ClassName() { 
    return String::New("Uint8"); 
}

} // namespace obotcha
