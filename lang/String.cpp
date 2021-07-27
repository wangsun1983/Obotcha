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

#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <sstream>
#include <algorithm>
#include <regex>
#include <string>

#include "String.hpp"
#include "ArrayList.hpp"
#include "NullPointerException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "TransformException.hpp"
#include "IllegalArgumentException.hpp"
#include "InitializeException.hpp"
#include "Error.hpp"

namespace obotcha {

const std::string _String::True = "true";

const std::string _String::False = "false";

const int _String::FormatBuffLength = 512;

const unsigned char _String::IgnoreCaseTable[128] = {
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x20/* */,0x21 /*!*/,0x22 /*"*/, 0x23 /*#*/,0x24/*$*/,0x25/*%*/,0x26/*&*/,0x27/*'*/, 
    0x28/*(*/,0x29 /*)*/,0x2A /***/, 0x2B /*+*/,0x2C/*,*/,0x2D/*-*/,0x2E/*.*/,0x2F/*/*/,
    0x30/*0*/,0x31 /*1*/,0x32 /*2*/, 0x33 /*3*/,0x34/*4*/,0x35/*5*/,0x36/*6*/,0x37/*7*/, 
    0x38/*8*/,0x39 /*9*/,0x3A /*:*/, 0x3B /*;*/,0x3C/*<*/,0x3D/*=*/,0x3E/*>*/,0x3F/*?*/,
    0x40/*@*/,0x41 /*A*/,0x42 /*B*/, 0x43 /*C*/,0x44/*D*/,0x45/*E*/,0x46/*F*/,0x47/*G*/, 
    0x48/*H*/,0x49 /*I*/,0x4A /*J*/, 0x4B /*K*/,0x4C/*L*/,0x4D/*M*/,0x4E/*N*/,0x4F/*O*/,
    0x50/*P*/,0x51 /*Q*/,0x52 /*R*/, 0x53 /*S*/,0x54/*T*/,0x55/*U*/,0x56/*V*/,0x57/*W*/, 
    0x58/*X*/,0x59 /*Y*/,0x5A /*Z*/, 0x5B /*[*/,0x5C/*\*/,0x5D/*]*/,0x5E/*^*/,0x5F/*_*/,
    0x60/*`*/,0x41 /*A*/,0x42 /*B*/, 0x43 /*C*/,0x44/*D*/,0x45/*E*/,0x46/*F*/,0x47/*G*/, 
    0x48/*H*/,0x49 /*I*/,0x4A /*J*/, 0x4B /*K*/,0x4C/*L*/,0x4D/*M*/,0x4E/*N*/,0x4F/*O*/,
    0x50/*P*/,0x51 /*Q*/,0x52 /*R*/, 0x53 /*S*/,0x54/*T*/,0x55/*U*/,0x56/*V*/,0x57/*W*/, 
    0x58/*X*/,0x59 /*Y*/,0x5A /*Z*/, 0x7B /*{*/,0x7C/*|*/,0x7D/*}*/,0x7E/*~*/,0x00
};

const unsigned char _String::toLowCaseTable[128] = {
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x20/* */,0x21 /*!*/,0x22 /*"*/, 0x23 /*#*/,0x24/*$*/,0x25/*%*/,0x26/*&*/,0x27/*'*/, 
    0x28/*(*/,0x29 /*)*/,0x2A /***/, 0x2B /*+*/,0x2C/*,*/,0x2D/*-*/,0x2E/*.*/,0x2F/*/*/,
    0x30/*0*/,0x31 /*1*/,0x32 /*2*/, 0x33 /*3*/,0x34/*4*/,0x35/*5*/,0x36/*6*/,0x37/*7*/, 
    0x38/*8*/,0x39 /*9*/,0x3A /*:*/, 0x3B /*;*/,0x3C/*<*/,0x3D/*=*/,0x3E/*>*/,0x3F/*?*/,
    0x40/*@*/,0x61 /*A*/,0x62 /*B*/, 0x63 /*C*/,0x64/*D*/,0x65/*E*/,0x66/*F*/,0x67/*G*/, 
    0x68/*H*/,0x69 /*I*/,0x6A /*J*/, 0x6B /*K*/,0x6C/*L*/,0x6D/*M*/,0x6E/*N*/,0x6F/*O*/,
    0x70/*P*/,0x71 /*Q*/,0x72 /*R*/, 0x73 /*S*/,0x74/*T*/,0x75/*U*/,0x76/*V*/,0x77/*W*/, 
    0x78/*X*/,0x79 /*Y*/,0x7A /*Z*/, 0x5B /*[*/,0x5C/*\*/,0x5D/*]*/,0x5E/*^*/,0x5F/*_*/,
    0x60/*`*/,0x61 /*A*/,0x62 /*B*/, 0x63 /*C*/,0x64/*D*/,0x65/*E*/,0x66/*F*/,0x67/*G*/, 
    0x68/*H*/,0x69 /*I*/,0x6A /*J*/, 0x6B /*K*/,0x6C/*L*/,0x6D/*M*/,0x6E/*N*/,0x6F/*O*/,
    0x70/*P*/,0x71 /*Q*/,0x72 /*R*/, 0x73 /*S*/,0x74/*T*/,0x75/*U*/,0x76/*V*/,0x77/*W*/, 
    0x78/*X*/,0x79 /*Y*/,0x7A /*Z*/, 0x7B /*{*/,0x7C/*|*/,0x7D/*}*/,0x7E/*~*/,0x00
};

const unsigned char _String::toUpCaseTable[128] = {
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
    0x20/* */,0x21 /*!*/,0x22 /*"*/, 0x23 /*#*/,0x24/*$*/,0x25/*%*/,0x26/*&*/,0x27/*'*/, 
    0x28/*(*/,0x29 /*)*/,0x2A /***/, 0x2B /*+*/,0x2C/*,*/,0x2D/*-*/,0x2E/*.*/,0x2F/*/*/,
    0x30/*0*/,0x31 /*1*/,0x32 /*2*/, 0x33 /*3*/,0x34/*4*/,0x35/*5*/,0x36/*6*/,0x37/*7*/, 
    0x38/*8*/,0x39 /*9*/,0x3A /*:*/, 0x3B /*;*/,0x3C/*<*/,0x3D/*=*/,0x3E/*>*/,0x3F/*?*/,
    0x40/*@*/,0x41 /*A*/,0x42 /*B*/, 0x43 /*C*/,0x44/*D*/,0x45/*E*/,0x46/*F*/,0x47/*G*/, 
    0x48/*H*/,0x49 /*I*/,0x4A /*J*/, 0x4B /*K*/,0x4C/*L*/,0x4D/*M*/,0x4E/*N*/,0x4F/*O*/,
    0x50/*P*/,0x51 /*Q*/,0x52 /*R*/, 0x53 /*S*/,0x54/*T*/,0x55/*U*/,0x56/*V*/,0x57/*W*/, 
    0x58/*X*/,0x59 /*Y*/,0x5A /*Z*/, 0x5B /*[*/,0x5C/*\*/,0x5D/*]*/,0x5E/*^*/,0x5F/*_*/,
    0x60/*`*/,0x41 /*A*/,0x42 /*B*/, 0x43 /*C*/,0x44/*D*/,0x45/*E*/,0x46/*F*/,0x47/*G*/, 
    0x48/*H*/,0x49 /*I*/,0x4A /*J*/, 0x4B /*K*/,0x4C/*L*/,0x4D/*M*/,0x4E/*N*/,0x4F/*O*/,
    0x50/*P*/,0x51 /*Q*/,0x52 /*R*/, 0x53 /*S*/,0x54/*T*/,0x55/*U*/,0x56/*V*/,0x57/*W*/, 
    0x58/*X*/,0x59 /*Y*/,0x5A /*Z*/, 0x7B /*{*/,0x7C/*|*/,0x7D/*}*/,0x7E/*~*/,0x00
};

_String::_String() {

}

_String::_String(const String &v) {
    m_str = v->m_str;
}

_String::_String(const Long &v) {
    m_str = std::to_string(v->toValue());
}

_String::_String(const Byte &v) {
    m_str = std::to_string(v->toValue());
}

_String::_String(const Uint8 &v) {
    m_str = std::to_string(v->toValue());
}

_String::_String(const Uint16 &v) {
    m_str = std::to_string(v->toValue());
}

_String::_String(const Uint32 &v) {
    m_str = std::to_string(v->toValue());
}

_String::_String(const Uint64 &v) {
    m_str = std::to_string(v->toValue());
}

_String::_String(const std::string v) {
    m_str = v;
}

_String::_String(std::string *v) {
    m_str = *v;
}

_String::_String(const Integer &v) {
    m_str = std::to_string(v->toValue());
}

_String::_String(const Boolean &v) {
    if(v->toValue()) {
        m_str = True;
    } else {
        m_str = False;
    }
}

_String::_String(const Float &v,int precision) {
    std::stringstream ss;
    ss.precision(precision);
    ss<< (double)v->toValue();
    ss>>m_str;
}

_String::_String(const Double &v,int precision) {
    std::stringstream ss;
    ss.precision(precision);
    ss<< v->toValue();
    ss>>m_str;
}

_String::_String(int v) {
    m_str = std::to_string(v);
}

_String::_String(bool v) {
    if(v) {
        m_str = True;
    } else {
        m_str = False;
    }
}

_String::_String(float v,int precision) {
    std::stringstream ss;
    ss.precision(precision);
    ss<< v;
    ss>>m_str;
}

_String::_String(double v,int precision) {
    std::stringstream ss;
    ss.precision(precision);
    ss<< v;
    ss>>m_str;
}

_String::_String(long v) {
    m_str = std::to_string(v);
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
    m_str = std::string(v);
}

_String::_String(const char *v,int start,int length) {
    if(start < 0 || length <=0 || ((start+length) > strlen(v))) {
        Trigger(InitializeException,"char * is null");
    }

    m_str = std::string(v,start,length);
}

_String::~_String() {
    //m_str = nullptr;
}

void _String::update(const char *v) {
    m_str = std::string(v);
}

void _String::update(const String &v) {
    m_str = v->m_str;
}

void _String::update(std::string v) {
    m_str = v;
}

const char * _String::toChars() {
    return m_str.c_str();
}

char _String::charAt(int index) {
    if(index >= m_str.size() || index < 0) {
        Trigger(ArrayIndexOutOfBoundsException,"incorrect index")
    }
    return m_str.data()[index];
}

String _String::subString(int start,int length) {
    if(start < 0 || length <= 0 ||((start + length) > m_str.length())) {
        return nullptr;
    }
    return createString(m_str.substr(start,length));
}

bool _String::contains(const String &val) {
    if(m_str.find(val->m_str) != m_str.npos) {
        return true;
    }

    return false;
}

bool _String::contains(std::string val) {
    if(m_str.find(val) != m_str.npos) {
        return true;
    }

    return false;
}
    
bool _String::contains(const char *val) {
    if(m_str.find(val) != m_str.npos) {
        return true;
    }

    return false;
}


String _String::trim() {
    if(m_str.size() != 0) {
        std::string trim_str = std::string(m_str);
        trim_str.erase(0,trim_str.find_first_not_of(" "));
        trim_str.erase(trim_str.find_last_not_of(" ") + 1);
        return createString(trim_str);
    }

    return nullptr;
}

String _String::trimAll() {
    if(m_str.size() != 0) {
        std::string trim_str = std::string(m_str);
        int index = 0;
        if(!trim_str.empty()) {
            while( (index = trim_str.find(' ',index)) != std::string::npos) {
                trim_str.erase(index,1);
            }
        }

        return createString(trim_str);
    }

    return nullptr;
}

int _String::size() {
    return m_str.size();
}

int _String::indexOf(const String &v) {
    return m_str.find(v->m_str);
}

int _String::indexOf(std::string v) {
    return m_str.find(v);
}

int _String::indexOf(const char *v) {
    return m_str.find(v);
}

int _String::indexOf(char v) {
    return m_str.find(v);
}
    
String _String::valueOf(const Integer &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(const Boolean &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(const Double &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(const Float &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(const Long &v) {
    return valueOf((uint64_t)v->toValue());
}

String _String::valueOf(const Uint8 &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(const Uint16 &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(const Uint32 &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(const Uint64 &v) {
    return valueOf(v->toValue());
}

String _String::valueOf(int v) {
    std::string str = std::to_string(v);
    return createString(str);
}

String _String::valueOf(std::uint16_t v) {
    std::string str = std::to_string(v);
    return createString(str);
}

String _String::valueOf(std::uint32_t v) {
    std::string str = std::to_string(v);
    return createString(str);
}

String _String::valueOf(std::uint64_t v) {
    std::string str = std::to_string(v);
    return createString(str);
}

String _String::valueOf(bool v) {
    if(v) {
        return createString(True);
    }

    return createString(False);
}

String _String::valueOf(double v) {
    std::stringstream ss;
    ss<< v;
    return createString(ss.str());
}

String _String::valueOf(float v) {
    std::stringstream ss;
    ss<< v;
    return createString(ss.str());
}

String _String::valueOf(const char *p) {
    if(p == nullptr) {
        return nullptr;
    }

    return createString(p);
}

uint64_t _String::hashcode() {
    return std::hash<std::string>{}(m_str);
}

bool _String::equals(const String &s) {
    return (m_str.compare(s->m_str) == 0);
}

bool _String::equals(const char *s) {
    return (m_str.compare(s) == 0);   
}

bool _String::equals(std::string p) {
    return (m_str.compare(p) == 0);
}

ArrayList<String> _String::split(const String &v) {
    return split(v->toChars(),v->size());
}

sp<_ArrayList<String>> _String::split(const char* v) {
    return split(v,strlen(v));
}

sp<_ArrayList<String>> _String::split(std::string separator) {
    
    ArrayList<String> t = createArrayList<String>();
    
    int index = 0;
    int last = 0;

    index = m_str.find_first_of(separator,last);

    if(index == -1) {
        return nullptr;
    }

    while(index != -1) {
        if(index != last) {
            t->add(createString(m_str.substr(last,index-last)));
        }
        last = index+1;
        index = m_str.find_first_of(separator,last);
    }
    
    if(last - m_str.size() > 0){
        t->add(createString(m_str.substr(last,index-last)));
    }

    return t;
}

sp<_ArrayList<String>> _String::split(const char* v,int size) {
    std::string str = std::string(v,size);

    return split(str);
}

Integer _String::toInteger() {
    return st(Integer)::parseDecInt(AutoClone(this));
}

Integer _String::toHexInt() {
    return st(Integer)::parseHexInt(AutoClone(this));
}

Integer _String::toOctInt() {
    return st(Integer)::parseOctInt(AutoClone(this));
}

Integer _String::toBinaryInt() {
    return st(Integer)::parseBinaryInt(AutoClone(this));
}

Byte _String::toByte() {
    return st(Byte)::parseDecByte(AutoClone(this));
}

Boolean _String::toBoolean() {
    return st(Boolean)::parse(AutoClone(this));
}

Float _String::toFloat() {
    return st(Float)::parse(AutoClone(this));
}

Double _String::toDouble() {
    return st(Double)::parse(AutoClone(this));
}

Long _String::toLong() {
    return st(Long)::parseDecLong(AutoClone(this));
}

Uint8 _String::toUint8() {
    return st(Uint8)::parseDecUint8(AutoClone(this));
}

Uint16 _String::toUint16() {
    return st(Uint16)::parseDecUint16(AutoClone(this));
}

Uint32 _String::toUint32() {
    return st(Uint32)::parseDecUint32(AutoClone(this));
}

Uint64 _String::toUint64() {
    return st(Uint64)::parseDecUint64(AutoClone(this));
}

uint8_t _String::toBasicUint8() {
    Uint8 value = toUint8();
    if(value == nullptr) {
        Trigger(TransformException,"String to Uint8 Fail");
    }

    return value->toValue();
}

uint16_t _String::toBasicUint16() {
    auto value = toUint16();
    if(value == nullptr) {
        Trigger(TransformException,"String to Uint16 Fail");
    }

    return value->toValue();
}

uint32_t _String::toBasicUint32() {
    auto value = toUint32();
    if(value == nullptr) {
        Trigger(TransformException,"String to Uint32 Fail");
    }

    return value->toValue();
}

uint64_t _String::toBasicUint64() {
    auto value = toUint64();
    if(value == nullptr) {
        Trigger(TransformException,"String to Uint64 Fail");
    }

    return value->toValue();
}

int _String::toBasicInt() {
    auto value = toInteger();
    if(value == nullptr) {
        Trigger(TransformException,"String to Integer Fail");
    }

    return value->toValue();
}

byte _String::toBasicByte() {
    auto value = toByte();
    if(value == nullptr) {
        Trigger(TransformException,"String to Byte Fail");
    }

    return value->toValue();
}

bool _String::toBasicBool() {
    Boolean value = toBoolean();

    if(value == nullptr) {
        Trigger(TransformException,"String to Boolean Fail");
    }

    return value->toValue();
}

float _String::toBasicFloat() {
    Float value = toFloat();

    if(value == nullptr) {
        Trigger(TransformException,"String to Float Fail");
    }

    return value->toValue();
}

double _String::toBasicDouble() {
    Double value = toDouble();

    if(value == nullptr) {
        Trigger(TransformException,"String to Double Fail");
    }

    return value->toValue();
}

long _String::toBasicLong() {
    Long value = toLong();

    if(value == nullptr) {
        Trigger(TransformException,"String to Long Fail");
    }

    return value->toValue();
}

ByteArray _String::toByteArray() {
    return createByteArray(m_str.c_str(),m_str.size());
}

std::string _String::getStdString() {
    return m_str;
}

String _String::toLowerCase() {
    int size = m_str.size();
    char data[m_str.size() + 1];

    const char *p = m_str.data();
    for(int i = 0;i < size;i++) {
        data[i] = toLowCaseTable[p[i]];
    }
    data[size] = 0;
    
    return createString((const char *)data); 
}

String _String::toUpperCase() {
    int size = m_str.size();
    char data[m_str.size() + 1];

    const char *p = m_str.data();
    for(int i = 0;i < size;i++) {
        data[i] = toUpCaseTable[p[i]];
    }
    data[size] = 0;
    
    return createString((const char *)data); 
}
    
bool _String::equalsIgnoreCase(const String &str) {
    return equalsIgnoreCase(str->toChars());
}

bool _String::equalsIgnoreCase(std::string str) {
    return equalsIgnoreCase(str.data());
}

bool _String::equalsIgnoreCase(const char * str) {
    return equalsIgnoreCase(str,strlen(str));
}

bool _String::equalsIgnoreCase(const char * str,int csize) {
    int size = m_str.size();
    if(csize > size) {
        return false;
    }

    return equalsIgnoreCase(str,m_str.c_str(),size);
}

bool _String::equalsIgnoreCase(const char *str1,const char *str2,int len) {
    int size = (len == -1)?strlen(str1):len;

    int index = 0;
    while(index < size) {
        int v1 = str1[index];
        int v2 = str2[index];
        if(IgnoreCaseTable[v1] != IgnoreCaseTable[v2]) {
            return false;
        }
        index++;
    }

    return true;
}

int _String::indexOfIgnoreCase(const String &str) {
    return indexOfIgnoreCase(str->toChars(),str->size());
}

int _String::indexOfIgnoreCase(std::string str) {
    return indexOfIgnoreCase(str.data(),str.size());
}

int _String::indexOfIgnoreCase(const char * str) {
    return indexOfIgnoreCase(str,strlen(str));
}

int _String::indexOfIgnoreCase(const char * str,int csize) {
    const char *m = m_str.data();
    
    int size = m_str.size();
    int index = 0;
    int subIndex = 0;
    int startIndex = -1;

    while(index < size) {
        //check whether there is a mark
        int v1 = m[index];
        int v2 = str[subIndex];
        if(IgnoreCaseTable[v1] == IgnoreCaseTable[v2]) {
            if(startIndex == -1) {
               startIndex = index;
            }

            index++;
            subIndex++;

            if(str[subIndex] == '\0') {
                return startIndex;
            }
            continue;
        }

        index++;
        subIndex = 0;
        startIndex = -1;

        if((index + csize) > size) {
            return -1;
        }
    }

    return -1;
}

bool _String::containsIgnoreCase(const String &val) {
    return (indexOfIgnoreCase(val) != -1);
}

bool _String::containsIgnoreCase(std::string val) {
    return (indexOfIgnoreCase(val) != -1);
}

bool _String::containsIgnoreCase(const char * val) {
    return (indexOfIgnoreCase(val) != -1);
}

bool _String::startsWithIgnoreCase(const String &str) {
    return (indexOfIgnoreCase(str) == 0);
}

bool _String::startsWithIgnoreCase(std::string str) {
    return (indexOfIgnoreCase(str) == 0);
}

bool _String::startsWithIgnoreCase(const char * str) {
    return (indexOfIgnoreCase(str) == 0);
}

bool _String::endsWithIgnoreCase(const String &s) {
    return endsWithIgnoreCase(s->toChars(),s->size());
}

bool _String::endsWithIgnoreCase(std::string str) {
    return endsWithIgnoreCase(str.data(),str.size());
}

bool _String::endsWithIgnoreCase(const char * str) {
    return endsWithIgnoreCase(str,strlen(str));
}

bool _String::endsWithIgnoreCase(const char * str,int csize) {
    int size = m_str.size();
    if(csize > size) {
        return false;
    }
    
    const char *m = m_str.data();
    int index = m_str.size() - 1;
    int subIndex = csize - 1;
    while(subIndex >= 0) {
        int v1 = m[index];
        int v2 = str[subIndex];
        if(IgnoreCaseTable[v1] != IgnoreCaseTable[v2]) {
            return false;
        }

        index--;
        subIndex--;
    }

    return true;
}

int _String::lastIndexOfIgnoreCase(const String &v) {
    return lastIndexOfIgnoreCase(v->toChars(),v->size());
}

int _String::lastIndexOfIgnoreCase(std::string v) {
    return lastIndexOfIgnoreCase(v.data(),v.size());
}

int _String::lastIndexOfIgnoreCase(const char * str) {
    return lastIndexOfIgnoreCase(str,strlen(str));
}

int _String::lastIndexOfIgnoreCase(const char * str,int csize) {
    int size = m_str.size();
    if(csize > size) {
        return -1;
    }
    
    const char *m = m_str.data();
    int index = m_str.size() - 1;
    int strEnd = csize - 1;
    int subIndex = strEnd;

    while(index >= subIndex) {
        int v1 = m[index];
        int v2 = str[subIndex];
        //printf("v2 is %d,v2 is %d,index is %d \n",v1,v2,index);
        if(IgnoreCaseTable[v1] == IgnoreCaseTable[v2]) {
            if(subIndex == 0) {
                return index;
            }

            index--;
            subIndex--;
            continue;
        }

        index--;
        subIndex = strEnd;
    }

    return -1;
}

bool _String::isEmpty() {
    return m_str.size() == 0;
}

bool _String::matches(const String &regex) {
    if(m_str.size() == 0) {
        if(regex != nullptr) {
            return false;    
        }
        return true;
    }

    return std::regex_match(m_str, std::regex(regex->m_str));
}

sp<_String> _String::replaceFirst(const String &regex,String value) {
    std::string result = std::regex_replace(m_str,std::regex(regex->m_str),value->m_str,
        std::regex_constants::format_first_only);
    return createString(result);
}

sp<_String> _String::replaceFirst(const char *regex,const char *v) {
    std::string result = std::regex_replace(m_str,std::regex(regex),v,
        std::regex_constants::format_first_only);

    return createString(result);
}

sp<_String> _String::replaceFirst(std::string regex,std::string v) {
    std::string result = std::regex_replace(m_str,std::regex(regex),v,
        std::regex_constants::format_first_only);

    return createString(result);
}

sp<_String> _String::replaceAll(const String &regex,const String &value) {
    std::string result = std::regex_replace(m_str,std::regex(regex->m_str),value->m_str);
    return createString(result);
}

sp<_String> _String::replaceAll(const char* regex,const char* v) {
    std::string result = std::regex_replace(m_str,std::regex(regex),v);
    return createString(result);
}

sp<_String> _String::replaceAll(std::string regex,std::string v) {
    std::string result = std::regex_replace(m_str,std::regex(regex),v);
    return createString(result);
}


bool _String::endsWith(const String &s) {
    std::string::size_type result = m_str.find_last_of(s->m_str);
    return (result == (m_str.size() - 1));
}

bool _String::endsWith(const char *s) {
    std::string::size_type result = m_str.find_last_of(s);
    return (result == (m_str.size() - 1));
}

bool _String::endsWith(std::string s) {
    std::string::size_type result = m_str.find_last_of(s);
    return (result == (m_str.size() - 1));
}


int _String::lastIndexOf(const String &v) {
    return m_str.find_last_of(v->m_str);
}

int _String::lastIndexOf(const char * v) {
    return m_str.find_last_of(v);
}

int _String::lastIndexOf(std::string v) {
    return m_str.find_last_of(v);
}

bool _String::startsWith(const String &v) {
    return (m_str.find(v->m_str) == v->size());
}

bool _String::startsWith(const char * v) {
    return (m_str.find(v) == strlen(v));
}

bool _String::startsWith(std::string v) {
    return (m_str.find(v) == v.size());
}

void _String::_append() {
    //Do nothing!!.just for _append
}

String _String::format(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    String str = _format(fmt, args);
    va_end(args);

    return str;
}

sp<_String> _String::className() {
    return createString("String");
}

String _String::_format(const char *fmt,va_list args) {
    constexpr size_t oldlen = FormatBuffLength;
    char buffer[oldlen];
    va_list argscopy;
    va_copy(argscopy, args);
    size_t newlen = vsnprintf(&buffer[0], oldlen, fmt, args) + 1;
    newlen++;  
    if (newlen > oldlen) {
        std::vector<char> newbuffer(newlen);
        vsnprintf(newbuffer.data(), newlen, fmt, argscopy);
        va_end(argscopy);
        return createString(newbuffer.data());
    }
    
    va_end(argscopy);
    return createString(buffer);
}



}