/**
 * @file String.cpp
 * @brief this class used for String
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>


#include "ArrayIndexOutOfBoundsException.hpp"
#include "ArrayList.hpp"
#include "Error.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "NullPointerException.hpp"
#include "String.hpp"
#include "TransformException.hpp"
#include "Inspect.hpp"

namespace obotcha {

const std::string _String::kTrue = "true";

const std::string _String::kFalse = "false";

const uint8_t _String::IgnoreCaseTable[128] = {
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x20 /* */, 0x21 /*!*/, 0x22 /*"*/, 0x23 /*#*/,
    0x24 /*$*/, 0x25 /*%*/, 0x26 /*&*/, 0x27 /*'*/, 0x28 /*(*/, 0x29 /*)*/,
    0x2A /***/, 0x2B /*+*/, 0x2C /*,*/, 0x2D /*-*/, 0x2E /*.*/, 0x2F /*/*/,
    0x30 /*0*/, 0x31 /*1*/, 0x32 /*2*/, 0x33 /*3*/, 0x34 /*4*/, 0x35 /*5*/,
    0x36 /*6*/, 0x37 /*7*/, 0x38 /*8*/, 0x39 /*9*/, 0x3A /*:*/, 0x3B /*;*/,
    0x3C /*<*/, 0x3D /*=*/, 0x3E /*>*/, 0x3F /*?*/, 0x40 /*@*/, 0x41 /*A*/,
    0x42 /*B*/, 0x43 /*C*/, 0x44 /*D*/, 0x45 /*E*/, 0x46 /*F*/, 0x47 /*G*/,
    0x48 /*H*/, 0x49 /*I*/, 0x4A /*J*/, 0x4B /*K*/, 0x4C /*L*/, 0x4D /*M*/,
    0x4E /*N*/, 0x4F /*O*/, 0x50 /*P*/, 0x51 /*Q*/, 0x52 /*R*/, 0x53 /*S*/,
    0x54 /*T*/, 0x55 /*U*/, 0x56 /*V*/, 0x57 /*W*/, 0x58 /*X*/, 0x59 /*Y*/,
    0x5A /*Z*/, 0x5B /*[*/, 0x5C /*\*/, 0x5D /*]*/, 0x5E /*^*/, 0x5F /*_*/,
    0x60 /*`*/, 0x41 /*A*/, 0x42 /*B*/, 0x43 /*C*/, 0x44 /*D*/, 0x45 /*E*/,
    0x46 /*F*/, 0x47 /*G*/, 0x48 /*H*/, 0x49 /*I*/, 0x4A /*J*/, 0x4B /*K*/,
    0x4C /*L*/, 0x4D /*M*/, 0x4E /*N*/, 0x4F /*O*/, 0x50 /*P*/, 0x51 /*Q*/,
    0x52 /*R*/, 0x53 /*S*/, 0x54 /*T*/, 0x55 /*U*/, 0x56 /*V*/, 0x57 /*W*/,
    0x58 /*X*/, 0x59 /*Y*/, 0x5A /*Z*/, 0x7B /*{*/, 0x7C /*|*/, 0x7D /*}*/,
    0x7E /*~*/, 0x00
};

const uint8_t _String::toLowCaseTable[128] = {
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x20 /* */, 0x21 /*!*/, 0x22 /*"*/, 0x23 /*#*/,
    0x24 /*$*/, 0x25 /*%*/, 0x26 /*&*/, 0x27 /*'*/, 0x28 /*(*/, 0x29 /*)*/,
    0x2A /***/, 0x2B /*+*/, 0x2C /*,*/, 0x2D /*-*/, 0x2E /*.*/, 0x2F /*/*/,
    0x30 /*0*/, 0x31 /*1*/, 0x32 /*2*/, 0x33 /*3*/, 0x34 /*4*/, 0x35 /*5*/,
    0x36 /*6*/, 0x37 /*7*/, 0x38 /*8*/, 0x39 /*9*/, 0x3A /*:*/, 0x3B /*;*/,
    0x3C /*<*/, 0x3D /*=*/, 0x3E /*>*/, 0x3F /*?*/, 0x40 /*@*/, 0x61 /*A*/,
    0x62 /*B*/, 0x63 /*C*/, 0x64 /*D*/, 0x65 /*E*/, 0x66 /*F*/, 0x67 /*G*/,
    0x68 /*H*/, 0x69 /*I*/, 0x6A /*J*/, 0x6B /*K*/, 0x6C /*L*/, 0x6D /*M*/,
    0x6E /*N*/, 0x6F /*O*/, 0x70 /*P*/, 0x71 /*Q*/, 0x72 /*R*/, 0x73 /*S*/,
    0x74 /*T*/, 0x75 /*U*/, 0x76 /*V*/, 0x77 /*W*/, 0x78 /*X*/, 0x79 /*Y*/,
    0x7A /*Z*/, 0x5B /*[*/, 0x5C /*\*/, 0x5D /*]*/, 0x5E /*^*/, 0x5F /*_*/,
    0x60 /*`*/, 0x61 /*A*/, 0x62 /*B*/, 0x63 /*C*/, 0x64 /*D*/, 0x65 /*E*/,
    0x66 /*F*/, 0x67 /*G*/, 0x68 /*H*/, 0x69 /*I*/, 0x6A /*J*/, 0x6B /*K*/,
    0x6C /*L*/, 0x6D /*M*/, 0x6E /*N*/, 0x6F /*O*/, 0x70 /*P*/, 0x71 /*Q*/,
    0x72 /*R*/, 0x73 /*S*/, 0x74 /*T*/, 0x75 /*U*/, 0x76 /*V*/, 0x77 /*W*/,
    0x78 /*X*/, 0x79 /*Y*/, 0x7A /*Z*/, 0x7B /*{*/, 0x7C /*|*/, 0x7D /*}*/,
    0x7E /*~*/, 0x00
};

const uint8_t _String::toUpCaseTable[128] = {
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x0,        0x0,        0x0,        0x0,
    0x0,        0x0,        0x20 /* */, 0x21 /*!*/, 0x22 /*"*/, 0x23 /*#*/,
    0x24 /*$*/, 0x25 /*%*/, 0x26 /*&*/, 0x27 /*'*/, 0x28 /*(*/, 0x29 /*)*/,
    0x2A /***/, 0x2B /*+*/, 0x2C /*,*/, 0x2D /*-*/, 0x2E /*.*/, 0x2F /*/*/,
    0x30 /*0*/, 0x31 /*1*/, 0x32 /*2*/, 0x33 /*3*/, 0x34 /*4*/, 0x35 /*5*/,
    0x36 /*6*/, 0x37 /*7*/, 0x38 /*8*/, 0x39 /*9*/, 0x3A /*:*/, 0x3B /*;*/,
    0x3C /*<*/, 0x3D /*=*/, 0x3E /*>*/, 0x3F /*?*/, 0x40 /*@*/, 0x41 /*A*/,
    0x42 /*B*/, 0x43 /*C*/, 0x44 /*D*/, 0x45 /*E*/, 0x46 /*F*/, 0x47 /*G*/,
    0x48 /*H*/, 0x49 /*I*/, 0x4A /*J*/, 0x4B /*K*/, 0x4C /*L*/, 0x4D /*M*/,
    0x4E /*N*/, 0x4F /*O*/, 0x50 /*P*/, 0x51 /*Q*/, 0x52 /*R*/, 0x53 /*S*/,
    0x54 /*T*/, 0x55 /*U*/, 0x56 /*V*/, 0x57 /*W*/, 0x58 /*X*/, 0x59 /*Y*/,
    0x5A /*Z*/, 0x5B /*[*/, 0x5C /*\*/, 0x5D /*]*/, 0x5E /*^*/, 0x5F /*_*/,
    0x60 /*`*/, 0x41 /*A*/, 0x42 /*B*/, 0x43 /*C*/, 0x44 /*D*/, 0x45 /*E*/,
    0x46 /*F*/, 0x47 /*G*/, 0x48 /*H*/, 0x49 /*I*/, 0x4A /*J*/, 0x4B /*K*/,
    0x4C /*L*/, 0x4D /*M*/, 0x4E /*N*/, 0x4F /*O*/, 0x50 /*P*/, 0x51 /*Q*/,
    0x52 /*R*/, 0x53 /*S*/, 0x54 /*T*/, 0x55 /*U*/, 0x56 /*V*/, 0x57 /*W*/,
    0x58 /*X*/, 0x59 /*Y*/, 0x5A /*Z*/, 0x7B /*{*/, 0x7C /*|*/, 0x7D /*}*/,
    0x7E /*~*/, 0x00
};

_String::_String(const Boolean &v):_String(v->toValue()? kTrue:kFalse) {
}

_String::_String(const String &v):_String(v->getStdString()) {
}

_String::_String(const Integer &v):_String(v->toValue()) {
}

_String::_String(const Long &v):_String(v->toValue()) {
}

_String::_String(const Byte &v):_String(v->toValue()) {
}

_String::_String(const Uint8 &v):_String(v->toValue()) {
}

_String::_String(const Uint16 &v):_String(v->toValue()) {
}

_String::_String(const Uint32 &v):_String(v->toValue()) {
}

_String::_String(const Uint64 &v):_String(v->toValue()) {
}

_String::_String(const std::string v) {
    m_str = v;
}

_String::_String(std::string *v) {
    Panic(v == nullptr,InitializeException,"create null string");
    m_str = *v;
}

_String::_String(unsigned char *v) {
    Panic(v == nullptr,InitializeException,"create null string");
    m_str = std::string((char *)v);
}

_String::_String(const Float &v, int precision):_String(v->toValue(),precision) {
}

_String::_String(const Double &v, int precision):_String(v->toValue(),precision) {
}

_String::_String(int v) {
    m_str = std::to_string(v);
}

_String::_String(float v, int precision) {
    std::stringstream ss;
    ss.precision(precision);
    ss << v;
    ss >> m_str;
}

_String::_String(double v, int precision) {
    std::stringstream ss;
    ss.precision(precision);
    ss << v;
    ss >> m_str;
}

_String::_String(long v) {
    m_str = std::to_string(v);
}

_String::_String(bool v) {
    m_str =(v)?kTrue:kFalse;
}

_String::_String(char v) {
    m_str = std::to_string(v);
}

_String::_String(uint8_t v) {
    m_str = std::to_string(v);
}

_String::_String(uint16_t v) {
    m_str = std::to_string(v);
}

_String::_String(uint32_t v) {
    m_str = std::to_string(v);
}

_String::_String(uint64_t v) {
    m_str = std::to_string(v);
}

_String::_String(const char *v) {
    Panic(v == nullptr,InitializeException,"create null string");
    m_str = std::string(v);
}

_String::_String(const char *v, int start,int length) {
    Panic(v == nullptr || start < 0 || length <= 0 || ((start + length) > strlen(v)),
        InitializeException, "char * is null");
    m_str = std::string(v + start, length);
}

void _String::update(const char *v) {
    m_str = std::string(v);
}

void _String::update(const String &v) {
    m_str = v->m_str;
}

void _String::update(const std::string &str) {
    m_str = str;
}

const char *_String::toChars() {
    return m_str.c_str();
}

const char *_String::toValue() {
    return m_str.c_str();
}

char _String::charAt(int index) {
    Panic(index >= m_str.size() || index < 0,
        ArrayIndexOutOfBoundsException, "incorrect index");
    return m_str.data()[index];
}

String _String::subString(int start, int length) {
    Panic(start < 0 || length <= 0 || ((start + length) > m_str.length()),
        ArrayIndexOutOfBoundsException, "incorrect start is %d,length is %d",start,length);
    return createString(m_str.substr(start, length));
}

bool _String::contains(const String &val) {
    return m_str.find(val->m_str) != m_str.npos;
}

bool _String::contains(const char *val) {
    return m_str.find(val) != m_str.npos;
}

String _String::trim() {
    if (m_str.size() != 0) {
        int start = m_str.find_first_not_of (' ');
        int end = m_str.find_last_not_of(' ');
        return createString(m_str.c_str(),start,end - start + 1);
    }

    return nullptr;
}

String _String::trimAll() {
    String str = createString(m_str);
    std::string::iterator end_pos = std::remove(str->m_str.begin(), str->m_str.end(), ' ');
    str->m_str.erase(end_pos, str->m_str.end());
    return str;
}

int _String::size() {
    return m_str.size();
}

int _String::indexOf(const String &v) {
    return m_str.find(v->m_str);
}

int _String::indexOf(const char *v) {
    return m_str.find(v);
}

int _String::indexOf(char v) {
    return m_str.find(v);
}

uint64_t _String::hashcode() const {
    return std::hash<std::string>{}(m_str);
}

bool _String::equals(Object s) {
    auto v = dynamic_cast<_String *>(s.get_pointer());
    return v == this ||
            ((v != nullptr) && (m_str.compare(v->m_str) == 0));
}

bool _String::sameAs(const char *s) {
    return m_str.compare(s) == 0;
}

bool _String::sameAs(const std::string &s) {
    return m_str.compare(s) == 0;
}

ArrayList<String> _String::split(const String &v) {
    return split(v->toChars(), v->size());
}

sp<_ArrayList<String>> _String::split(const char *v) {
    return split(v, strlen(v));
}

sp<_ArrayList<String>> _String::split(const char *v, int size) {
    std::string separator = std::string(v, size);
    ArrayList<String> t = createArrayList<String>();
    int index = 0;
    int last = 0;
    index = m_str.find_first_of(separator, last);
    while (index != std::string::npos) {
        if (index > last) {
            t->add(createString(m_str.substr(last, index - last)));
        }
        last = index + 1;
        index = m_str.find_first_of(separator, last);
    }

    if (last != 0 && last != m_str.size()) {
        t->add(createString(m_str.substr(last, index - last)));
    }

    return t;
}

int _String::counts(String str) {
    int count = 0;
    int index = 0;
    while ((index = m_str.find(str->m_str, index)) != std::string::npos) {
        count++;
        index++;
    }

    return count;
}

//find
int _String::find(String s,int start) {
    return m_str.find(s->m_str, start);
}

Integer _String::toInteger() {
    return st(Integer)::ParseDecString(AutoClone(this));
}

Integer _String::toHexInt() {
    return st(Integer)::ParseHexString(AutoClone(this));
}

Integer _String::toOctInt() {
    return st(Integer)::ParseOctString(AutoClone(this));
}

Integer _String::toBinaryInt() {
    return st(Integer)::ParseBinaryString(AutoClone(this));
}

Byte _String::toByte() {
    return st(Byte)::ParseDecString(AutoClone(this));
}

Boolean _String::toBoolean() {
    return st(Boolean)::Parse(AutoClone(this));
}

Float _String::toFloat() {
    return st(Float)::Parse(AutoClone(this));
}

Double _String::toDouble() {
    return st(Double)::Parse(AutoClone(this));
}

Long _String::toLong() {
    return st(Long)::ParseDecLong(AutoClone(this));
}

Uint8 _String::toUint8() {
    return st(Uint8)::ParseDecString(AutoClone(this));
}

Uint16 _String::toUint16() {
    return st(Uint16)::ParseDecString(AutoClone(this));
}

Uint32 _String::toUint32() {
    return st(Uint32)::ParseDecString(AutoClone(this));
}

Uint64 _String::toUint64() {
    return st(Uint64)::ParseDecString(AutoClone(this));
}

uint8_t _String::toBasicUint8() {
    Uint8 value = toUint8();
    Panic(value == nullptr,TransformException, "String to Uint8 Fail");
    return value->toValue();
}

uint16_t _String::toBasicUint16() {
    auto value = toUint16();
    Panic(value == nullptr,TransformException, "String to Uint16 Fail");
    return value->toValue();
}

uint32_t _String::toBasicUint32() {
    auto value = toUint32();
    Panic(value == nullptr,TransformException, "String to Uint32 Fail");
    return value->toValue();
}

uint64_t _String::toBasicUint64() {
    auto value = toUint64();
    Panic(value == nullptr,TransformException, "String to Uint64 Fail");
    return value->toValue();
}

int _String::toBasicInt() {
    auto value = toInteger();
    Panic(value == nullptr,TransformException, "String to Integer Fail");
    return value->toValue();
}

byte _String::toBasicByte() {
    auto value = toByte();
    Panic(value == nullptr,TransformException, "String to Byte Fail");
    return value->toValue();
}

bool _String::toBasicBool() {
    Boolean value = toBoolean();
    Panic(value == nullptr,TransformException, "String to Boolean Fail");
    return value->toValue();
}

float _String::toBasicFloat() {
    Float value = toFloat();
    Panic(value == nullptr,TransformException, "String to Float Fail");
    return value->toValue();
}

double _String::toBasicDouble() {
    Double value = toDouble();
    Panic(value == nullptr,TransformException, "String to Double Fail");
    return value->toValue();
}

long _String::toBasicLong() {
    Long value = toLong();
    Panic(value == nullptr,TransformException, "String to Long Fail");
    return value->toValue();
}

ByteArray _String::toByteArray() {
    return createByteArray((byte *)m_str.c_str(), m_str.size());
}

bool _String::regionMatches(int toffset, String other, int ooffset,int len) {
    // Note: toffset, ooffset, or len might be near -1>>>1.
    Inspect((ooffset < 0) || (toffset < 0)
            || (toffset > (long)size() - len)
            || (ooffset > (long)other->size() - len),false)

    while (len-- > 0) {
        Inspect(charAt(toffset++) != other->charAt(ooffset++),false)
    }

    return true;
}

bool _String::regionMatchesIgnoreCase(int toffset, String other, int ooffset,int len) {
    // Note: toffset, ooffset, or len might be near -1>>>1.
    Inspect((ooffset < 0) || (toffset < 0)
            || (toffset > (long)size() - len)
            || (ooffset > (long)other->size() - len),false)

    while (len-- > 0) {
        Inspect(IgnoreCaseTable[charAt(toffset++)]
            != IgnoreCaseTable[other->charAt(ooffset++)],false)
    }
    return true;
}

sp<_String> _String::clone() {
    return createString(m_str.c_str());
}

std::string _String::getStdString() {
    return m_str;
}

String _String::toLowerCase() {
    int size = m_str.size();
    char data[m_str.size() + 1];

    const char *p = m_str.data();
    for (int i = 0; i < size; i++) {
        data[i] = toLowCaseTable[p[i]];
    }
    data[size] = 0;

    return createString((const char *)data);
}

String _String::toUpperCase() {
    int size = m_str.size();
    char data[m_str.size() + 1];

    const char *p = m_str.data();
    for (int i = 0; i < size; i++) {
        data[i] = toUpCaseTable[p[i]];
    }
    data[size] = 0;

    return createString((const char *)data);
}

bool _String::equalsIgnoreCase(const String &str) {
    Inspect(str->size() != size(),false)
    return EqualsIgnoreCase(m_str.c_str(),str->m_str.c_str());
}

bool _String::equalsIgnoreCase(const std::string str) {
    Inspect(str.size() != size(),false)
    return EqualsIgnoreCase(m_str.c_str(),str.c_str());
}

bool _String::equalsIgnoreCase(const char *str, int size) {
    if(size == -1) {
        size = strlen(str);
    }

    return (size == m_str.size())?EqualsIgnoreCase(str, m_str.c_str(), size):false;
}

bool _String::EqualsIgnoreCase(const char *str1, const char *str2, int len) {
    int size = (len == -1) ? strlen(str1) : len;

    int index = 0;
    while (index < size) {
        int v1 = str1[index];
        int v2 = str2[index];
        if (IgnoreCaseTable[v1] != IgnoreCaseTable[v2]) {
            return false;
        }
        index++;
    }

    return true;
}

int _String::indexOfIgnoreCase(const String &str) {
    return indexOfIgnoreCase(str->toChars(), str->size());
}

int _String::indexOfIgnoreCase(const std::string &str) {
    return indexOfIgnoreCase(str.c_str(), str.size());
}

int _String::indexOfIgnoreCase(const char *str) {
    return indexOfIgnoreCase(str, strlen(str));
}

int _String::indexOfIgnoreCase(const char *str, int csize) {
    const char *m = m_str.data();
    int size = m_str.size();
    Inspect(csize > size,-1)

    int index = 0;
    int compareIndex = 0;
    int startIndex = -1;

    while (index < size) {
        // check whether there is a mark
        int v1 = m[index];
        int v2 = str[compareIndex];
        if (IgnoreCaseTable[v1] == IgnoreCaseTable[v2]) {
            if (startIndex == -1) {
                startIndex = index;
            }

            index++;
            compareIndex++;
            if (compareIndex == csize) {
                return startIndex;
            }
            continue;
        }

        index++;

        if(startIndex != -1) {
            compareIndex = 0;
            startIndex = -1;
        }

        if ((index + csize) > size) {
            return -1;
        }
    }

    return -1;
}

bool _String::containsIgnoreCase(const String &val) {
    return indexOfIgnoreCase(val) != -1;
}

bool _String::containsIgnoreCase(const char *val) {
    return indexOfIgnoreCase(val) != -1;
}

bool _String::containsIgnoreCase(const std::string &val) {
    return indexOfIgnoreCase(val) != -1;
}

bool _String::startsWithIgnoreCase(const String &str) {
    return indexOfIgnoreCase(str) == 0;
}

bool _String::startsWithIgnoreCase(const char *str) {
    return indexOfIgnoreCase(str) == 0;
}

bool _String::startsWithIgnoreCase(const std::string &str) {
    return indexOfIgnoreCase(str) == 0;
}

bool _String::endsWithIgnoreCase(const String &s) {
    return endsWithIgnoreCase(s->toChars(), s->size());
}

bool _String::endsWithIgnoreCase(const char *str) {
    return endsWithIgnoreCase(str, strlen(str));
}

bool _String::endsWithIgnoreCase(const std::string &str) {
    return endsWithIgnoreCase(str.c_str(), str.size());
}

bool _String::endsWithIgnoreCase(const char *str, int csize) {
    int size = m_str.size();
    Inspect(csize > size,false)

    const char *m = m_str.data();
    int index = m_str.size() - 1;
    int compareIndex = csize - 1;
    while (compareIndex >= 0) {
        int v1 = m[index];
        int v2 = str[compareIndex];
        if (IgnoreCaseTable[v1] != IgnoreCaseTable[v2]) {
            return false;
        }

        index--;
        compareIndex--;
    }

    return true;
}

int _String::lastIndexOfIgnoreCase(const String &v) {
    return lastIndexOfIgnoreCase(v->toChars(), v->size());
}

int _String::lastIndexOfIgnoreCase(const char *str) {
    return lastIndexOfIgnoreCase(str, strlen(str));
}

int _String::lastIndexOfIgnoreCase(const std::string &str) {
    return lastIndexOfIgnoreCase(str.c_str(),str.size());
}

int _String::lastIndexOfIgnoreCase(const char *str, int csize) {
    int size = m_str.size();
    Inspect(csize > size,-1)

    const char *m = m_str.data();
    int index = m_str.size() - 1;
    int compareIndex = csize - 1;

    while (index >= compareIndex) {
        int v1 = m[index];
        int v2 = str[compareIndex];
        if (IgnoreCaseTable[v1] == IgnoreCaseTable[v2]) {
            if (compareIndex == 0) {
                return index;
            }

            index--;
            compareIndex--;
            continue;
        }

        index--;
        compareIndex = csize - 1;
    }

    return -1;
}

bool _String::isEmpty() {
  return m_str.size() == 0;
}

bool _String::matches(const String &regex) {
    Inspect(m_str.size() == 0,false)
    return std::regex_match(m_str, std::regex(regex->m_str));
}

bool _String::Equals(sp<_String> a,sp<_String> b) {
    return (a != nullptr && b != nullptr)?a->equals(b):false;
}

String _String::toString() {
    return createString(m_str);
}

sp<_String> _String::replaceFirst(const String &regex,const String &value) {
    std::string result = std::regex_replace(m_str,
                                            std::regex(regex->m_str),
                                            value->m_str,
                                            std::regex_constants::format_first_only);
    return createString(result);
}

sp<_String> _String::replaceAll(const String &regex, const String &value) {
    std::string result = std::regex_replace(m_str,
                                            std::regex(regex->m_str),
                                            value->m_str);
    return createString(result);
}

bool _String::endsWith(const String &s) {
    std::string::size_type result = m_str.find_last_of(s->m_str);
    return result == (m_str.size() - 1);
}

bool _String::endsWith(const char *s) {
    std::string::size_type result = m_str.find_last_of(s);
    return result == (m_str.size() - 1);
}

bool _String::endsWith(const std::string &s) {
    return endsWith(s.c_str());
}

int _String::lastIndexOf(const String &v) {
    return m_str.find_last_of(v->m_str);
}

int _String::lastIndexOf(const char *v) {
    return m_str.find_last_of(v);
}

int _String::lastIndexOf(const std::string &v) {
    return lastIndexOf(v.c_str());
}

bool _String::startsWith(const String &v) {
    return m_str.find(v->m_str) == 0;
}

bool _String::startsWith(const char *v) {
    return m_str.find(v) == 0;
}

bool _String::startsWith(const std::string &v) {
    return m_str.find(v) == 0;
}

void _String::_append() {
    // Do nothing!!.just for _append
}

sp<_String> _String::ClassName() {
    return createString("String");
}

} // namespace obotcha
