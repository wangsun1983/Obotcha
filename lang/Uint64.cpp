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
#include "NumberTransformer.hpp"

namespace obotcha {

_Uint64::_Uint64(uint64_t v) : mValue(v) {
}

_Uint64::_Uint64(const Uint64 &v) : mValue(v->mValue) {
}

uint64_t _Uint64::toValue() const { 
    return mValue; 
}

bool _Uint64::equals(Object p) { 
    auto v = dynamic_cast<_Uint64 *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

bool _Uint64::sameAs(uint64_t p) const { 
     return mValue == p; 
}

void _Uint64::update(uint64_t v) { 
    mValue = v; 
}

void _Uint64::update(const sp<_Uint64> &v) { 
    mValue = v->mValue; 
}

sp<_String> _Uint64::toHexString() const {
    return createString(st(NumberTransformer)::ToHexString(mValue));
}

sp<_String> _Uint64::toOctalString() const {
    return createString(st(NumberTransformer)::ToOctalString(mValue));
}

sp<_String> _Uint64::toBinaryString() const {
    return createString(st(NumberTransformer)::ToBinaryString(mValue));
}

sp<_String> _Uint64::toString() {
    return createString(st(NumberTransformer)::ToDecString(mValue));
}

sp<_String> _Uint64::ToString(uint64_t v) {
    return createString(st(NumberTransformer)::ToDecString(v));
}

sp<_Uint64> _Uint64::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

sp<_Uint64> _Uint64::ParseDecString(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseDecNumber<uint64_t>(v->getStdString());
        return createUint64(value);
    )
    return nullptr;
}

sp<_Uint64> _Uint64::ParseHexString(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseHexNumber<uint64_t>(v->getStdString());
        return createUint64(value);
    )

    return nullptr;
}

sp<_Uint64> _Uint64::ParseOctString(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseOctNumber<uint64_t>(v->getStdString());
        return createUint64(value);
    )

    return nullptr;
}

sp<_Uint64> _Uint64::ParseBinaryString(const sp<_String> &v) {
    NoException(
        auto value = st(NumberTransformer)::ParseBinaryNumber<uint64_t>(v->getStdString());
        return createUint64(value);
    )

    return nullptr;
}

sp<_String> _Uint64::ClassName() { 
    return createString("Uint64"); 
}

uint64_t _Uint64::hashcode() const { 
    return std::hash<uint64_t>{}(mValue); 
}

} // namespace obotcha
