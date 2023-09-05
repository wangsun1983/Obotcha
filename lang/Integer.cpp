/**
 * @file Integer.cpp
 * @brief this class used for int
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include <algorithm>
#include <bitset>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <memory>

#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "Integer.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include "NumberTransformer.hpp"

namespace obotcha {

const int _Integer::kMaxValue = 0x7fffffff;

const int _Integer::kMinValue = 0x80000000;

_Integer::_Integer(int v) : mValue(v) {
    //Nothing
}

_Integer::_Integer(const Integer &v):mValue(v->toValue()) {
}

int _Integer::toValue() const {
    return mValue;
}

bool _Integer::equals(Object p) {
    auto v = dynamic_cast<_Integer *>(p.get_pointer());
    return v != nullptr && mValue == v->mValue;
}

uint64_t _Integer::hashcode() const {
    return std::hash<int>{}(mValue);
}

bool _Integer::sameAs(int p) const{
     return mValue == p;
}

void _Integer::update(int v) {
    mValue = v;
}

void _Integer::update(const sp<_Integer> &v) {
    mValue = v->mValue;
}

// 16
sp<_String> _Integer::toHexString() const {
    return createString(st(NumberTransformer)::ToHexString(mValue));
}

// 10
sp<_String> _Integer::toString() {
    return createString(st(NumberTransformer)::ToDecString(mValue));
}

// 8
sp<_String> _Integer::toOctalString() const {
    return createString(st(NumberTransformer)::ToOctalString(mValue));
}

// 2
sp<_String> _Integer::toBinaryString() const {
    return createString(st(NumberTransformer)::ToBinaryString(mValue));
}

sp<_String> _Integer::ToString(int v) {
    return createString(st(NumberTransformer)::ToDecString(v));
}

sp<_Integer> _Integer::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

Integer _Integer::ParseDecString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseDecNumber<int>(v->getStdString());
        return createInteger(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

Integer _Integer::ParseHexString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseHexNumber<int>(v->getStdString());
        return createInteger(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

Integer _Integer::ParseOctString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseOctNumber<int>(v->getStdString());
        return createInteger(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

Integer _Integer::ParseBinaryString(const sp<_String> &v) {
    try {
        auto value = st(NumberTransformer)::ParseBinaryNumber<int>(v->getStdString());
        return createInteger(value);
    } catch(TransformException &) {
        return nullptr;
    }
}

String _Integer::ClassName() {
    return createString("Integer");
}

} // namespace obotcha
