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

#include <string.h>

#include "String.hpp"
#include "ArrayList.hpp"
#include "NullPointerException.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "TransformException.hpp"

namespace obotcha {

const static std::string TRUE_STRING = "true";

const static std::string FALSE_STRING = "false";

_String::_String() {

}

_String::_String(String v) {
    if(v.m_ptr != nullptr) {
        m_str = v->m_str;
    }
}

_String::_String(Long &v) {
    if(v == nullptr) {
        throw NullPointerException("Long is null");
    }

    std::stringstream ss;
    long value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Byte &v) {
    if(v == nullptr) {
        throw NullPointerException("Byte is null");
    }

    std::stringstream ss;
    byte value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint8 &v) {
    if(v == nullptr) {
        throw NullPointerException("Uint8 is null");
    }

    std::stringstream ss;
    uint8_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint16 &v) {
    if(v == nullptr) {
        throw NullPointerException("Uint16 is null");
    }

    std::stringstream ss;
    uint16_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint32 &v) {
    if(v == nullptr) {
        throw NullPointerException("Uint32 is null");
    }

    std::stringstream ss;
    uint32_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint64 &v) {
    if(v == nullptr) {
        throw NullPointerException("Uint64 is null");
    }

    std::stringstream ss;
    uint64_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(const std::string &v) {
    m_str = v;
}

_String::_String(std::string *v) {
    if(v == nullptr) {
        throw NullPointerException("std::string is null");
    }
    m_str = *v;
}

_String::_String(Integer &v) {
    if(v == nullptr) {
        throw NullPointerException("Integer is null");
    }

    std::stringstream ss;
    int value = v->toValue();
    ss<<value;

    m_str =  ss.str();
}

_String::_String(Boolean &v) {
    if(v == nullptr) {
        throw NullPointerException("Boolean is null");
    }

    bool value = v->toValue();
    if(value) {
        m_str = TRUE_STRING;
    } else {
        m_str = FALSE_STRING;
    }
}

_String::_String(Float &v) {
    if(v == nullptr) {
        throw NullPointerException("Float is null");
    }

    std::stringstream ss;
    float value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Double &v) {
    if(v == nullptr) {
        throw NullPointerException("Double is null");
    }
    
    std::stringstream ss;
    double value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(int v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(bool v) {
    if(v) {
        m_str = TRUE_STRING;
    } else {
        m_str = FALSE_STRING;
    }
}

_String::_String(float v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(double v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(long v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(char v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(uint8_t v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(uint16_t v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(uint32_t v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(uint64_t v) {
    std::stringstream ss;
    ss<<v;
    m_str = ss.str();
}

_String::_String(const char *v) {
    if(v == nullptr) {
        throw NullPointerException("char * is null");
    }
    
    m_str = std::string(v);
}

_String::_String(const char *v,int start,int length) {    
    m_str = std::string(v,start,length);
}

_String::~_String() {
    //TODO
}

const char * _String::toChars() {
    return m_str.data();
}

char _String::charAt(int index) {
    if(index < 0 || (unsigned int)index >= m_str.size()) {
        throw ArrayIndexOutOfBoundsException("char At error");
    }

    return m_str.data()[index];
}

String _String::subString(int start,int end) {
    if(end < 0 ||start > end || (uint32_t)end >= m_str.size()) {
        return nullptr;
    }

    return createString(m_str.substr(start,end));
}

bool _String::contains(String val) {

    if(val == nullptr) {
        return false;
    }

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
    if(val == nullptr) {
        return false;
    }

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
        return new _String(trim_str);
    }

    return nullptr;
}

String _String::trimAll() {
    if(m_str.size() != 0) {
        String ss = createString(m_str);
        return ss->replaceAll(" ","");
    }

    return nullptr;
}

int _String::size() {
    return m_str.size();
}

String _String::append(String s) {
    if(s == nullptr) {
        return createString(m_str);
    }

    String result = append(s->toChars());
    return result;
}

String _String::append(std::string s) {
    return append(s.data());
}

String _String::append(const char *p) {
    if(p == nullptr) {
        return createString(m_str);
    }
    return createString(m_str.append(p));
}

int _String::indexOf(String v) {
    if(v == nullptr) {
        return -1;
    }

    return m_str.find(v->m_str);
}

int _String::indexOf(std::string v) {
    return m_str.find(v);
}

int _String::indexOf(const char *v) {
    if(v == nullptr) {
        return -1;
    }

    return m_str.find(v);
}
    
String _String::valueOf(Integer &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Boolean &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Double &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Float &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Long &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf((uint64_t)v->toValue());
}

String _String::valueOf(Uint8 &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Uint16 &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Uint32 &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Uint64 &v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(int v) {
    stringstream ss;
    ss<< v;
    std::string temp = ss.str();
    return createString(temp);
}

String _String::valueOf(std::uint16_t v) {
    stringstream ss;
    ss<< v;
    std::string temp = ss.str();
    return createString(temp);
}

String _String::valueOf(std::uint32_t v) {
    stringstream ss;
    ss<< v;
    std::string temp = ss.str();
    return createString(temp);
}

String _String::valueOf(std::uint64_t v) {
    stringstream ss;
    ss<< v;
    std::string temp = ss.str();
    return createString(temp);
}

String _String::valueOf(bool v) {
    if(v) {
        return createString(TRUE_STRING);
    }

    return createString(FALSE_STRING);
}

String _String::valueOf(double v) {
    stringstream ss;
    ss<< v;
    return createString(ss.str());
}

String _String::valueOf(float v) {
    stringstream ss;
    ss<< v;
    return createString(ss.str());
}

String _String::valueOf(const char *p) {
    if(p == nullptr) {
        return nullptr;
    }

    return createString(p);
}

bool _String::equals(String s) {
    if(s == nullptr) {
        return false;
    }

    return (m_str.compare(s->m_str) == 0);
}

bool _String::equals(const char *s) {
    if(s == nullptr) {
        return false;
    }

    return (m_str.compare(s) == 0);   
}

bool _String::equals(const std::string p) {
    return (m_str.compare(p) == 0);
}

ArrayList<String> _String::split(String v) {
    return split(v->toChars());
}

sp<_ArrayList<String>> _String::split(const char* v) {
    if(v == nullptr) {
        return nullptr;
    }

    ArrayList<String> t = createArrayList<String>();
    int index = 0;
    int last = 0;

    index = m_str.find_first_of(v,last);

    if(index == -1) {
        return nullptr;
    }

    while(index != -1) {
        t->add(createString(m_str.substr(last,index-last)));
        last = index+1;
        index = m_str.find_first_of(v,last);
    }
    
    if(last - m_str.size() > 0){
        t->add(createString(m_str.substr(last,index-last)));
    }

    return t;
}

sp<_ArrayList<String>> _String::split(std::string v) {
    return split(v.c_str());
}

Integer _String::toInteger() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    int value;
    ss>>value;
    
    return createInteger(value);
}

Boolean _String::toBoolean() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    const char *data = m_str.data();

    if( (m_str.size() == 4) &&
        (data[0] == 't' || data[0] == 'T')
        &&(data[1] == 'r' || data[1] == 'R')
        &&(data[2] == 'u' || data[2] == 'U')
        &&(data[3] == 'e' || data[3] == 'E')) {
        return createBoolean(true);
    }

    if((m_str.size() == 5) &&
        (data[0] == 'f' || data[0] == 'F')
        &&(data[1] == 'a' || data[1] == 'A')
        &&(data[2] == 'l' || data[2] == 'L')
        &&(data[3] == 's' || data[3] == 'S')
        &&(data[4] == 'e' || data[4] == 'E')) {
        return createBoolean(false);
    }

    return nullptr;
}

Float _String::toFloat() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isFloatNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    float value;
    ss>>value;
    
    return createFloat(value);
}

Double _String::toDouble() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isDoubleNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    float value;
    ss>>value;
    
    return createDouble(value);
}

Long _String::toLong() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isLongNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    long value;
    ss>>value;
    
    return createLong(value);
}

Uint8 _String::toUint8() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    uint8_t value;
    ss>>value;
    
    return createUint8(value);
}

Uint16 _String::toUint16() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    uint16_t value;
    ss>>value;
    
    return createUint16(value);
}

Uint32 _String::toUint32() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    uint32_t value;
    ss>>value;
    
    return createUint32(value);
}

Uint64 _String::toUint64() {
    if(m_str.size() == 0) {
        return nullptr;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return nullptr;
    }

    std::stringstream ss;
    ss<<m_str;
    uint64_t value;
    ss>>value;
    
    return createUint64(value);
}

uint8_t _String::toBasicUint8() {
    if(m_str.size() == 0 ||!isIntNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Uint8 Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    uint8_t value;
    ss>>value;
    return value;
}

uint16_t _String::toBasicUint16() {
    if((m_str.size() == 0) || !isIntNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Uint16 Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    uint16_t value;
    ss>>value;
    return value;
}

uint32_t _String::toBasicUint32() {
    if((m_str.size() == 0) ||!isIntNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Uint32 Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    uint32_t value;
    ss>>value;
    return value;
}

uint64_t _String::toBasicUint64() {
    if((m_str.size() == 0) ||!isIntNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Uint64 Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    uint64_t value;
    ss>>value;
    return value;
}

int _String::toBasicInt() {
    if((m_str.size() == 0) || !isIntNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Int Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    int value;
    ss>>value;
    return value;
}

int _String::toHexInt() {
    if(m_str.size() == 0 || !isIntNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Hex Int Fail");
    }

    std::stringstream ss;
    ss<< std::hex <<m_str;
    int value;
    ss>>value;
    return value;
}

String _String::toHexString() {
    if(m_str.size() == 0 || !isIntNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Hex Int Fail");
    }

    int v = toBasicInt();
    std::string value;
    std::stringstream ss;
    ss<<std::hex<<v;
    ss>>value;
    printf("changeHex value is %s \n",value.c_str());
    return createString(value);
}

bool _String::toBasicBool() {
    if(m_str.size() == 0) {
        throw TransformException("String to Boolean Fail");
    }

    const char *data = m_str.data();
    
    if( (m_str.size() == 4) &&
        (data[0] == 't' || data[0] == 'T')
        &&(data[1] == 'r' || data[1] == 'R')
        &&(data[2] == 'u' || data[2] == 'U')
        &&(data[3] == 'e' || data[3] == 'E')) {
        return true;
    }

    if((m_str.size() == 5) &&
        (data[0] == 'f' || data[0] == 'F')
        &&(data[1] == 'a' || data[1] == 'A')
        &&(data[2] == 'l' || data[2] == 'L')
        &&(data[3] == 's' || data[3] == 'S')
        &&(data[4] == 'e' || data[4] == 'E')) {
        throw TransformException("String to Boolean Fail");
    }

    return false;
}

float _String::toBasicFloat() {
    if(m_str.size() == 0 || !isFloatNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Float Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    float value;
    ss>>value;
    return value;
}

double _String::toBasicDouble() {
    if(m_str.size() == 0 || !isDoubleNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Double Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    double value;
    ss>>value;
    return value;
}

long _String::toBasicLong() {
    if(m_str.size() == 0 || !isLongNumber(m_str.data(),m_str.size())) {
        throw TransformException("String to Long Fail");
    }

    std::stringstream ss;
    ss<<m_str;
    long value;
    ss>>value;
    return value;
}

std::string _String::getStdString() {
    return m_str;
}

String _String::toLowerCase() {
    String result = createString(m_str);
    std::transform(result->m_str.begin(),result->m_str.end(),result->m_str.begin(),::tolower);
    return result;
}

String _String::toUpperCase() {
    String result = createString(m_str);
    std::transform(result->m_str.begin(),result->m_str.end(),result->m_str.begin(),::toupper);
    return result;
}
    
bool _String::equalsIgnoreCase(String str) {
    if(str == nullptr) {
        return false;
    }

    return equalsIgnoreCase(str->toChars());
}

bool _String::equalsIgnoreCase(std::string str) {
    return equalsIgnoreCase(str.data());
}

bool _String::equalsIgnoreCase(const char * str) {
    if(str == nullptr) {
        return false;
    }
    
    const char *m = m_str.data();
    int index = 0;
    while(1) {
        if(m[index] != str[index]) {
            if((m[index] != (str[index] + 32)) &&
               (m[index] != (str[index] - 32))) {
                return false;
            }
        }

        if(m[index] == '\0') {
            break;
        }

        index++;
    }

    return true;
}

int _String::indexOfIgnoreCase(String str) {
    if(str == nullptr) {
        return  -1;
    }
    return indexOfIgnoreCase(str->toChars());
}

int _String::indexOfIgnoreCase(std::string str) {
    return indexOfIgnoreCase(str.data());
}

int _String::indexOfIgnoreCase(const char * str) {
    if(str == nullptr) {
        return  -1;
    }
    const char *m = m_str.data();
    int index = 0;
    int subIndex = 0;
    int startIndex = -1;
    while(1) {
        if(m[index] == str[subIndex] ||
           m[index] == str[subIndex] + 32 ||
           m[index] == str[subIndex] - 32) {
           if(startIndex == -1) {
               startIndex = index;
           }

           index++;
           subIndex++;
           continue;
        }

        if(str[subIndex] == '\0') {
            return startIndex;
        }

        if(m[index] == '\0') {
            return -1;
        }

        index++;
        subIndex = 0;
        startIndex = -1;
    }
}

bool _String::containsIgnoreCase(String val) {
    if(val == nullptr) {
        return false;
    }
    return (indexOfIgnoreCase(val) != -1);
}

bool _String::containsIgnoreCase(std::string val) {
    return (indexOfIgnoreCase(val) != -1);
}

bool _String::containsIgnoreCase(const char * val) {
    if(val == nullptr) {
        return false;
    }
    return (indexOfIgnoreCase(val) != -1);
}

bool _String::startsWithIgnoreCase(String str) {
    if(str == nullptr) {
        return false;
    }
    return (indexOfIgnoreCase(str) == 0);
}

bool _String::startsWithIgnoreCase(std::string str) {
    return (indexOfIgnoreCase(str) == 0);
}

bool _String::startsWithIgnoreCase(const char * str) {
    if(str == nullptr) {
        return false;
    }
    return (indexOfIgnoreCase(str) == 0);
}

bool _String::endsWithIgnoreCase(String s) {
    if(s == nullptr) {
        return false;
    }
    
    return endsWithIgnoreCase(s->toChars());
}

bool _String::endsWithIgnoreCase(std::string str) {
    return endsWithIgnoreCase(str.data());
}

bool _String::endsWithIgnoreCase(const char * str) {
    if(str == nullptr) {
        return false;
    }

    const char *m = m_str.data();
    int index = m_str.size() - 1;
    int subIndex = strlen(str) - 1;
    while(1) {
        if((m[index] != str[subIndex]) &&
           (m[index] != str[subIndex] + 32) &&
           (m[index] != str[subIndex] - 32)) {
            return false;
        }

        if(subIndex == 0) {
            return true;
        }

        if(index == 0) {
            return false;
        }

        index--;
        subIndex--;
    }

    return false;
}

int _String::lastIndexOfIgnoreCase(String v) {
    if(v == nullptr) {
        return false;
    }
    return lastIndexOfIgnoreCase(v->toChars());
}

int _String::lastIndexOfIgnoreCase(std::string v) {
    return lastIndexOfIgnoreCase(v.data());
}

int _String::lastIndexOfIgnoreCase(const char * str) {
    if(str == nullptr) {
        return false;
    }

    const char *m = m_str.data();
    int index = m_str.size() - 1;
    int strEnd = strlen(str) - 1;
    int subIndex = strEnd;
    while(1) {
        if((m[index] == str[subIndex]) ||
           (m[index] == str[subIndex] + 32) ||
           (m[index] == str[subIndex] - 32)) {
            if(subIndex == 0) {
                return index;
            }

            index--;
            subIndex--;
            continue;
        }

        if(index == 0) {
            return -1;
        }

        index--;
        subIndex = strEnd;
    }

    return -1;
}


bool _String::isEmpty() {
    return m_str.size() == 0;
}

bool _String::matches(String regex) {
    if(m_str.size() == 0) {
        if(regex != nullptr) {
            return false;    
        }
        return true;
    }

    return std::regex_match(m_str, std::regex(regex->m_str));
}

sp<_String> _String::replaceFirst(String regex,String value) {
    if(m_str.size() == 0 || value == nullptr || regex == nullptr) {
        return nullptr;
    }

    std::string result = std::regex_replace(m_str,std::regex(regex->m_str),value->m_str,
        std::regex_constants::format_first_only);
    return createString(result);
}

sp<_String> _String::replaceFirst(const char *regex,const char *v) {
    if(regex == nullptr || v == nullptr) {
        return nullptr;
    }

    std::string result = std::regex_replace(m_str,std::regex(regex),v,
        std::regex_constants::format_first_only);

    return createString(result);
}

sp<_String> _String::replaceFirst(std::string regex,std::string v) {
    std::string result = std::regex_replace(m_str,std::regex(regex),v,
        std::regex_constants::format_first_only);

    return createString(result);
}

sp<_String> _String::replaceAll(String regex,String value) {
    if(m_str.size() == 0 || value == nullptr || regex == nullptr) {
        return nullptr;
    }
    std::string result = std::regex_replace(m_str,std::regex(regex->m_str),value->m_str);
    return createString(result);
}

sp<_String> _String::replaceAll(const char* regex,const char* v) {
    if(regex == nullptr || v == nullptr) {
        return nullptr;
    }

    std::string result = std::regex_replace(m_str,std::regex(regex),v);
    return createString(result);
}

sp<_String> _String::replaceAll(std::string regex,std::string v) {
    std::string result = std::regex_replace(m_str,std::regex(regex),v);
    return createString(result);
}


bool _String::endsWith(String s) {
    if(m_str.size() == 0 || m_str.size() == 0 || s == nullptr) {
        return false;
    }

    string::size_type result = m_str.find_last_of(s->m_str);
    return (result == (m_str.size() - 1));
}

bool _String::endsWith(const char *s) {
    if(s == nullptr) {
        return false;
    }

    string::size_type result = m_str.find_last_of(s);
    return (result == (m_str.size() - 1));
}

bool _String::endsWith(std::string s) {
    string::size_type result = m_str.find_last_of(s);
    return (result == (m_str.size() - 1));
}


int _String::lastIndexOf(String v) {
    if(m_str.size() == 0 || m_str.size() == 0 || v == nullptr) {
        return -1;
    }

    int result = m_str.find_last_of(v->m_str);
    return result;
}

int _String::lastIndexOf(const char * v) {
    if(v == nullptr) {
        return -1;
    }

    int result = m_str.find_last_of(v);
    return result;
}

int _String::lastIndexOf(std::string v) {
    return m_str.find_last_of(v);
}


bool _String::startsWith(String v) {
    if(m_str.size() == 0 || m_str.size() == 0 || v == nullptr) {
        return false;
    }

    int result = m_str.find(v->m_str);
    return (result == v->size());
}

bool _String::startsWith(const char * v) {
    if(v == nullptr) {
        return false;
    }

    string::size_type result = m_str.find(v);
    return (result == strlen(v));
}

bool _String::startsWith(std::string v) {
    string::size_type result = m_str.find(v);
    return (result == v.size());
}

bool _String::isIntNumber(const char *p,int size) {
    for(int i = 0;i < size;i++) {
        if(p[i] >= '0' && p[i] <= '9') {
            continue;
        } else {
            if((i == size - 1) && p[i] == '\0') {
                return true;
            }
            return false;
        }
    }

    return true;
}

bool _String::isLongNumber(const char *p,int size) {
    for(int i = 0;i < size;i++) {
        if(p[i] >= '0' && p[i] <= '9') {
            continue;
        }
        return false;
    }

    return true;
}

bool _String::isDoubleNumber(const char *p,int size) {
    int dotCount = 0;

    for(int i = 0;i < size;i++) {
        if(p[i] >= '0' && p[i] <= '9') {
            continue;
        } else if(p[i] == '.') {
            dotCount++;
            if(dotCount > 1) {
                return false;
            }
            continue;
        }
        return false;
    }

    return true;
}

bool _String::isFloatNumber(const char *p,int size) {
    int dotCount = 0;

    for(int i = 0;i < size;i++) {
        if(p[i] >= '0' && p[i] <= '9') {
            continue;
        } else if(p[i] == '.') {
            dotCount++;
            if(dotCount > 1) {
                return false;
            }
            continue;
        }
        return false;
    }
    return true;
}

}