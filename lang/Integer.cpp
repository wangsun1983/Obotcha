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
#include <memory.h>
#include <sstream>
#include <stdio.h>

#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "Integer.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"

namespace obotcha {

const int _Integer::MAX_VALUE = 0x7fffffff;

const int _Integer::MIN_VALUE = 0x80000000;

_Integer::_Integer() : val(0) {
    //Nothing
}

_Integer::_Integer(int v) : val(v) {
    //Nothing
}

_Integer::_Integer(const Integer &v) {
    Panic(v == nullptr,InitializeException, "Object is null");
    val = v->toValue();
}

int _Integer::toValue() {
    return val;
}

bool _Integer::equals(Object p) {
    auto v = dynamic_cast<_Integer *>(p.get_pointer());
    return v != nullptr && val == v->val;
}

uint64_t _Integer::hashcode() const {
    return std::hash<int>{}(val);
}

// bool _Integer::equals(int p) {
//     return val == p;
// }

// bool _Integer::equals(const _Integer *p) {
//     return val == p->val;
// }

void _Integer::update(int v) {
    val = v;
}

void _Integer::update(const sp<_Integer> &v) {
    val = v->val;
}

// 16
sp<_String> _Integer::toHexString() {
    return createString(_Number::ToHexString(val));
}

// 10
sp<_String> _Integer::toString() {
    return createString(_Number::ToDecString(val));
}

// 8
sp<_String> _Integer::toOctalString() {
    return createString(_Number::ToOctalString(val));
}

// 2
sp<_String> _Integer::toBinaryString() {
    return createString(_Number::ToBinaryString(val));
}

sp<_String> _Integer::ToString(int i) {
    return createString(_Number::ToDecString(i));
}

sp<_Integer> _Integer::Parse(const sp<_String> &v) {
    return ParseDecString(v);
}

Integer _Integer::ParseDecString(const sp<_String> &v) {
    NoException(
        int value = _Number::ParseDecNumber(v->getStdString());
        return createInteger(value);
    );
    return nullptr;
}

Integer _Integer::ParseHexString(const sp<_String> &v) {
    NoException(
        int value = _Number::ParseHexNumber(v->getStdString());
        return createInteger(value);
    );
    return nullptr;
}

Integer _Integer::ParseOctString(const sp<_String> &v) {
    NoException(
        int value = _Number::ParseOctNumber(v->getStdString());
        return createInteger(value);
    );
    return nullptr;
}

Integer _Integer::ParseBinaryString(const sp<_String> &v) {
    NoException(
        int value = _Number::ParseBinaryNumber(v->getStdString());
        return createInteger(value);
    );

    return nullptr;
}

String _Integer::ClassName() {
    return createString("Integer");
}

} // namespace obotcha
