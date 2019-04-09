#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <sstream>
#include <algorithm>
#include <regex>

#include "String.hpp"

namespace obotcha {

 _String::_String() {
    m_str = new std::string();
}

_String::_String(String v) {
    if(v.m_ptr == nullptr) {
        //TOOD
    } else {
        if(v->m_str != nullptr) {
            m_str = new std::string(v->m_str->data());
        } else {
            m_str = new std::string();
        }
    }
}

_String::_String(Long v) {
    std::stringstream ss;
    long value = v->toValue();
    ss<<value;

    m_str = new std::string(ss.str());
}

_String::_String(std::string v) {
    m_str = new std::string(v);
}

_String::_String(std::string *v) {
    m_str = new std::string(*v);
}

_String::_String(Integer v) {
    std::stringstream ss;
    int value = v->toValue();
    ss<<value;

    m_str = new std::string(ss.str());
}

_String::_String(Boolean v) {
    bool value = v->toValue();
    if(value) {
        m_str = new std::string("true");
    } else {
        m_str = new std::string("false");
    }
}

_String::_String(Float v) {
    std::stringstream ss;
    float value = v->toValue();
    ss<<value;

    m_str = new std::string(ss.str());
}

_String::_String(Double v) {
    std::stringstream ss;
    double value = v->toValue();
    ss<<value;

    m_str = new std::string(ss.str());
}

_String::_String(int v) {
    std::stringstream ss;
    ss<<v;
    m_str = new std::string(ss.str());
}

_String::_String(bool v) {
    if(v) {
        m_str = new std::string("true");
    } else {
        m_str = new std::string("false");
    }
}

_String::_String(float v) {
    std::stringstream ss;
    ss<<v;
    m_str = new std::string(ss.str());
}

_String::_String(double v) {
    std::stringstream ss;
    ss<<v;
    m_str = new std::string(ss.str());
}

_String::_String(long v) {
    std::stringstream ss;
    ss<<v;
    m_str = new std::string(ss.str());
}

_String::_String(const char *v) {
    m_str = new std::string(v);
}

_String::_String(char *v,int start,int length) {
    m_str = new std::string(v,start,length);
}

_String::~_String() {
    if(m_str != nullptr) {       
        delete m_str;
    }
}

const char * _String::toChars() {
    return m_str->data();
}

char _String::charAt(int index) {
    return m_str->data()[index];
}

String _String::subString(int start,int end) {
    if(start > end || end >= m_str->size()) {
        return new _String((std::string *)nullptr);
    }

    std::string *result = new std::string(m_str->substr(start,end));
    String ret = new _String(result);
    return ret;
}

bool _String::contains(String val) {
    if(m_str != nullptr) {
        if(m_str->find(*val->m_str) != -1) {
            return true;
        }
    }

    return false;
}

String _String::trim() {
    if(m_str != nullptr) {
        std::string *trim_str = new std::string(*m_str);
        trim_str->erase(0,trim_str->find_first_not_of(" "));
        trim_str->erase(trim_str->find_last_not_of(" ") + 1);
        return new _String(trim_str);
    }

    return new _String(m_str);
}

int _String::size() {
    return m_str->size();
}

void _String::append(String s) {
    m_str->append(*s->m_str);
    //printf("string is %s \n",m_str->data());
}

void _String::append(const char *p) {
    m_str->append(p);
}

int _String::indexOf(String v) {
    if(m_str != nullptr) {
        return m_str->find(*v->m_str);
    }

    return -1;
}
    
String _String::valueOf(Integer v) {
    return valueOf(v->toValue());
}

String _String::valueOf(Boolean v) {
    return valueOf(v->toValue());
}

String _String::valueOf(Double v) {
    return valueOf(v->toValue());
}

String _String::valueOf(Float v) {
    return valueOf(v->toValue());
}

String _String::valueOf(int v) {
    stringstream ss;
    ss<< v;
    std::string *temp = new std::string(ss.str());
    String value = new _String(temp);
    return value;
}

String _String::valueOf(bool v) {
    if(v) {
        std::string *temp = new std::string("true");
        String value = new _String(temp);
        return value;
    }

    std::string *temp = new std::string("false");
    String value = new _String(temp);
    return value;
}

String _String::valueOf(double v) {
    stringstream ss;
    ss<< v;
    std::string *temp = new std::string(ss.str());
    String value = new _String(temp);
    return value;
}

String _String::valueOf(float v) {
    stringstream ss;
    ss<< v;
    std::string *temp = new std::string(ss.str());
    String value = new _String(temp);
    return value;
}

String _String::valueOf(char *p) {
    return createString(p);
}

bool _String::equals(String s) {
    if(m_str == nullptr) {
        if(s == nullptr) {
            return true;
        }

        return false;
    }

    return (m_str->compare(*s->m_str) == 0);
}

bool _String::equals(const char *s) {
    if(m_str == nullptr) {
        if(s == nullptr) {
            return true;
        }

        return false;
    }

    return (m_str->compare(s) == 0);   
}

bool _String::equals(const std::string p) {
    if(m_str == nullptr) {
        return false;
    }

    return (m_str->compare(p) == 0);
}


Integer _String::toInteger() {
    int v = toBasicInt();
    return createInteger(v);
}

Boolean _String::toBoolean() {
    bool v = toBasicBool();
    return createBoolean(v);
}

Float _String::toFloat() {
    float v = toBasicFloat();
    return createFloat(v);
}

Double _String::toDouble() {
    double v = toBasicDouble();
    return createDouble(v);
}

int _String::toBasicInt() {
    std::stringstream ss;
    ss<<*m_str;
    int value;
    ss>>value;
    return value;
}

bool _String::toBasicBool() {
    if(m_str->compare("true") == 0) {
        return true;
    }

    return false;
}

float _String::toBasicFloat() {
    std::stringstream ss;
    ss<<*m_str;
    float value;
    ss>>value;
    return value;
}

double _String::toBasicDouble() {
    std::stringstream ss;
    ss<<*m_str;
    double value;
    ss>>value;
    return value;
}

std::string _String::getStdString() {
    if(m_str == nullptr) {
        printf("getStdString is null \n");
    }
    return *m_str;
}

String _String::toLowerCase() {
    if(m_str == nullptr) {
        return nullptr;
    }

    String result = createString(*m_str);
    std::transform(result->m_str->begin(),result->m_str->end(),result->m_str->begin(),::tolower);
    return result;
}

String _String::toUpperCase() {
    if(m_str == nullptr) {
        return nullptr;
    }
    
    String result = createString(*m_str);
    std::string strTmp = *result->m_str;
    std::transform(strTmp.begin(),strTmp.end(),strTmp.begin(),::toupper);
    return result;
}
    
bool _String::equalsIgnoreCase(String str) {
    if(m_str == nullptr) {
        if(str == nullptr) {
            return true;
        }
        return true;
    } 
    
    String str1 = createString(*m_str);
    String str2 = createString(str);

    std::string std_str1 = *str1->m_str;
    std::string std_str2 = *str2->m_str;

    std::transform(std_str1.begin(),std_str1.end(),std_str1.begin(),::toupper);
    std::transform(std_str2.begin(),std_str2.end(),std_str2.begin(),::toupper);

    return (std_str1.compare(std_str2) == 0);
}

bool _String::containsIgnoreCase(String val) {
    if(m_str == nullptr) {
        if(val == nullptr) {
            return true;
        }
        return true;
    }

    String str1 = createString(*m_str);
    String str2 = createString(val);

    std::string std_str1 = *str1->m_str;
    std::string std_str2 = *str2->m_str;

    std::transform(std_str1.begin(),std_str1.end(),std_str1.begin(),::toupper);
    std::transform(std_str2.begin(),std_str2.end(),std_str2.begin(),::toupper);
    return (std_str1.find(std_str2) != -1);
}

bool _String::isEmpty() {
    if(m_str == nullptr) {
        return true;
    }
    return m_str->size() == 0;
}

bool _String::matches(String regex) {
    if(m_str == nullptr) {
        if(regex != nullptr) {
            return false;    
        }
        return true;
    }

    return std::regex_match(*m_str, std::regex(*regex->m_str));
}

sp<_String> _String::replaceFirst(String regex,String value) {
    if(m_str == nullptr || value == nullptr || regex == nullptr) {
        return nullptr;
    }

    std::string result = std::regex_replace(*m_str,std::regex(*regex->m_str),*value->m_str,
        std::regex_constants::format_first_only);
    return createString(result);
}

sp<_String> _String::replaceAll(String regex,String value) {
    if(m_str == nullptr || value == nullptr || regex == nullptr) {
        return nullptr;
    }    
    
    std::string result = std::regex_replace(*m_str,std::regex(*regex->m_str),*value->m_str);
    return createString(result);
}

bool _String::endsWith(String s) {
    if(m_str == nullptr || m_str->size() == 0) {
        return false;
    }

    int result = m_str->find_last_of(*s->m_str);
    return (result == m_str->size() - 1);
}

int _String::lastIndexOf(String v) {
    int result = m_str->find_last_of(*v->m_str);
    return result;
}

bool _String::startsWith(String v) {
    int result = m_str->find(*v->m_str);
    return (result == v->size());
}




}