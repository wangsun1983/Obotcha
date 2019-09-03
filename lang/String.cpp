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

namespace obotcha {

#ifdef DEBUG_STRING_MEMORY_LEAK
static int stringCount;
#endif

const static std::string TRUE_STRING = "true";

const static std::string FALSE_STRING = "false";

_String::_String() {
    ////m_str = new std::string();

#ifdef DEBUG_STRING_MEMORY_LEAK    
    stringCount++;
    stringId = stringCount;
    printf("wangsl,a count is %d,str is %s \n",stringId,m_str.data());
#endif
}

_String::_String(String v) {
    if(v.m_ptr != nullptr) {
        m_str = v->m_str;
    } 

#ifdef DEBUG_STRING_MEMORY_LEAK    
    stringCount++;
    stringId = stringCount;
    printf("wangsl,b count is %d,str is %s \n",stringId,m_str.data());
#endif   
}

_String::_String(Long v) {
    if(v == nullptr) {
        return;
    }

    std::stringstream ss;
    long value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Byte v) {
    if(v == nullptr) {
        return;
    }

    std::stringstream ss;
    byte value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint8 v) {
    if(v == nullptr) {
        return;
    }

    std::stringstream ss;
    uint8_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint16 v) {
    if(v == nullptr) {
        return;
    }

    std::stringstream ss;
    uint16_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint32 v) {
    if(v == nullptr) {
        return;
    }

    std::stringstream ss;
    uint32_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Uint64 v) {
    if(v == nullptr) {
        return;
    }

    std::stringstream ss;
    uint64_t value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(std::string v) {
    m_str = v;
}

_String::_String(std::string *v) {
    m_str = *v;
}

_String::_String(Integer v) {
    if(v == nullptr) {
        return;
    }

    std::stringstream ss;
    int value = v->toValue();
    ss<<value;

    m_str =  ss.str();
}

_String::_String(Boolean v) {
    if(v == nullptr) {
        return;
    }

    bool value = v->toValue();
    if(value) {
        m_str = TRUE_STRING;
    } else {
        m_str = FALSE_STRING;
    }
}

_String::_String(Float v) {
    if(v == nullptr) {
        ////m_str = new std::string();
        return;
    }

    std::stringstream ss;
    float value = v->toValue();
    ss<<value;

    m_str = ss.str();
}

_String::_String(Double v) {
    if(v == nullptr) {
        //m_str = new std::string();
        return;
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

_String::_String(byte v) {
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
    if(v != nullptr) {
        m_str = std::string(v);
    }

#ifdef DEBUG_STRING_MEMORY_LEAK    
    stringCount++;
    stringId = stringCount;
    printf("wangsl,e count is %d,str is %s \n",stringId,m_str.data());
#endif 
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
    if(m_str.size() == 0) {
        return -1;
    }

    if(index >= m_str.size()) {
        return -1;    
    }

    return m_str.data()[index];
}

String _String::subString(int start,int end) {
    if(start > end || end >= m_str.size()) {
        return nullptr;
    }

    return createString(m_str.substr(start,end));
}

bool _String::contains(String val) {

    if(val == nullptr) {
        return false;
    }

    if(m_str.find(val->m_str) != -1) {
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
    //m_str.append(*s->m_str);
    //printf("string is %s \n",m_str.data());
    String str = createString(m_str);

    if(s == nullptr) {
        return str;
    }

    return str->append(s->toChars());
}

String _String::append(const char *p) {
    String newStr = createString(m_str);
    if(p == nullptr) {
        return newStr;
    }

    newStr->m_str.append(p);
    return newStr;
}

int _String::indexOf(String v) {
    if(v == nullptr) {
        return -1;
    }

    return m_str.find(v->m_str);
}
    
String _String::valueOf(Integer v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Boolean v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Double v) {
    if(v == nullptr) {
        return nullptr;
    }

    return valueOf(v->toValue());
}

String _String::valueOf(Float v) {
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
    if(m_str.size() == 0) {
        if(s == nullptr) {
            return true;
        }

        return false;
    }

    if(s == nullptr) {
        return false;
    }

    return (m_str.compare(s) == 0);   
}

bool _String::equals(const std::string p) {

    if(m_str.size() == 0) {
        if(p.size() == 0) {
            return true;
        }

        return false;
    }

    return (m_str.compare(p) == 0);
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
    if(m_str.size() == 0) {
        return -1;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return -1;
    }

    std::stringstream ss;
    ss<<m_str;
    uint8_t value;
    ss>>value;
    return value;
}

uint16_t _String::toBasicUint16() {
    if(m_str.size() == 0) {
        return -1;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return -1;
    }

    std::stringstream ss;
    ss<<m_str;
    uint16_t value;
    ss>>value;
    return value;
}

uint32_t _String::toBasicUint32() {
    if(m_str.size() == 0) {
        return -1;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return -1;
    }

    std::stringstream ss;
    ss<<m_str;
    uint32_t value;
    ss>>value;
    return value;
}

uint64_t _String::toBasicUint64() {
    if(m_str.size() == 0) {
        return -1;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return -1;
    }

    std::stringstream ss;
    ss<<m_str;
    uint64_t value;
    ss>>value;
    return value;
}

int _String::toBasicInt() {
    if(m_str.size() == 0) {
        return 0;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return 0;
    }

    std::stringstream ss;
    ss<<m_str;
    int value;
    ss>>value;
    return value;
}

int _String::toHexInt() {
    if(m_str.size() == 0) {
        return 0;
    }

    if(!isIntNumber(m_str.data(),m_str.size())) {
        return 0;
    }

    std::stringstream ss;
    ss<< std::hex <<m_str;
    int value;
    ss>>value;
    return value;
}

bool _String::toBasicBool() {
    if(m_str.size() == 0) {
        return false;
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
        return false;
    }

    return false;
}

float _String::toBasicFloat() {
    if(m_str.size() == 0) {
        return 0;
    }

    if(!isFloatNumber(m_str.data(),m_str.size())) {
        return 0;
    }

    std::stringstream ss;
    ss<<m_str;
    float value;
    ss>>value;
    return value;
}

double _String::toBasicDouble() {
    if(m_str.size() == 0) {
        return 0;
    }

    if(!isDoubleNumber(m_str.data(),m_str.size())) {
        return 0;
    }

    std::stringstream ss;
    ss<<m_str;
    double value;
    ss>>value;
    return value;
}

long _String::toBasicLong() {
    if(m_str.size() == 0) {
        return 0;
    }

    if(!isLongNumber(m_str.data(),m_str.size())) {
        return 0;
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
    if(m_str.size() == 0) {
        if(str == nullptr) {
            return true;
        }
        return false;
    }
    
    String str1 = createString(m_str);
    String str2 = createString(str);

    std::string std_str1 = str1->m_str;
    std::string std_str2 = str2->m_str;

    std::transform(std_str1.begin(),std_str1.end(),std_str1.begin(),::toupper);
    std::transform(std_str2.begin(),std_str2.end(),std_str2.begin(),::toupper);

    return (std_str1.compare(std_str2) == 0);
}

int _String::indexOfIgnoreCase(String str) {
    if(m_str.size() == 0) {
        if(str == nullptr) {
            return true;
        }
        return false;
    }

    String str1 = createString(m_str);
    String str2 = createString(str);

    std::string std_str1 = str1->m_str;
    std::string std_str2 = str2->m_str;

    std::transform(std_str1.begin(),std_str1.end(),std_str1.begin(),::toupper);
    std::transform(std_str2.begin(),std_str2.end(),std_str2.begin(),::toupper);
    
    return std_str1.find(std_str2);
}

bool _String::containsIgnoreCase(String val) {
    if(m_str.size() == 0) {
        if(val == nullptr) {
            return true;
        }
        return true;
    }

    String str1 = createString(m_str);
    String str2 = createString(val);

    std::string std_str1 = str1->m_str;
    std::string std_str2 = str2->m_str;

    std::transform(std_str1.begin(),std_str1.end(),std_str1.begin(),::toupper);
    std::transform(std_str2.begin(),std_str2.end(),std_str2.begin(),::toupper);
    return (std_str1.find(std_str2) != -1);
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

sp<_String> _String::replaceAll(String regex,String value) {
    if(m_str.size() == 0 || value == nullptr || regex == nullptr) {
        return nullptr;
    }
    std::string result = std::regex_replace(m_str,std::regex(regex->m_str),value->m_str);
    return createString(result);
}

bool _String::endsWith(String s) {
    if(m_str.size() == 0 || m_str.size() == 0 || s == nullptr) {
        return false;
    }

    int result = m_str.find_last_of(s->m_str);
    return (result == m_str.size() - 1);
}

int _String::lastIndexOf(String v) {
    if(m_str.size() == 0 || m_str.size() == 0 || v == nullptr) {
        return -1;
    }

    int result = m_str.find_last_of(v->m_str);
    return result;
}

bool _String::startsWith(String v) {
    if(m_str.size() == 0 || m_str.size() == 0 || v == nullptr) {
        return false;
    }

    int result = m_str.find(v->m_str);
    return (result == v->size());
}

bool _String::isIntNumber(const char *p,int size) {
    for(int i = 0;i < size;i++) {
        if(p[i] >= '0' && p[i] <= '9') {
            continue;
        } else {
            if((i == size - 1) && p[i] == '\n') {
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