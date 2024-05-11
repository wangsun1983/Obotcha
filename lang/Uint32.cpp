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
#include "Uint32.hpp"
#include "String.hpp"
#include "NumberTransformer.hpp"

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
    return String::New(st(NumberTransformer)::ToHexString(mValue));
}

sp<_String> _Uint32::toOctalString() const {
    return String::New(st(NumberTransformer)::ToOctalString(mValue));
}

sp<_String> _Uint32::toBinaryString() const {
    return String::New(st(NumberTransformer)::ToBinaryString(mValue));
}

sp<_String> _Uint32::toString() {
    return String::New(st(NumberTransformer)::ToDecString(mValue));
}

sp<_String> _Uint32::ToString(uint32_t v) {
    return String::New(st(NumberTransformer)::ToDecString(v));
}

sp<_Uint32> _Uint32::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Uint32> _Uint32::ParseDecString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseDecNumber<uint32_t>(v->getStdString());
        return Uint32::New(value);
    } catch(TransformException &) {
        return nullptr;
    }    
}

sp<_Uint32> _Uint32::ParseHexString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseHexNumber<uint32_t>(v->getStdString());
        return Uint32::New(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Uint32> _Uint32::ParseOctString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseOctNumber<uint32_t>(v->getStdString());
        return Uint32::New(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_Uint32> _Uint32::ParseBinaryString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseBinaryNumber<uint32_t>(v->getStdString());
        return Uint32::New(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

sp<_String> _Uint32::ClassName() { 
    return String::New("Uint32");
}

uint64_t _Uint32::hashcode() const { 
    return std::hash<uint32_t>{}(mValue); 
}

} // namespace obotcha
