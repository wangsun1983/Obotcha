#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <string>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Integer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Long.hpp"

using namespace std;

#define const_str(Y) createString(Y)

namespace obotcha {

DECLARE_SIMPLE_CLASS(String)
{
public:
    _String();

    _String(std::string *v);

    _String(std::string v);

    _String(String v);

    _String(const char *v);

    _String(char *v,int start,int length);

    _String(Integer v);

    _String(Boolean v);

    _String(Float v);

    _String(Double v);

    _String(Long v);

    _String(int v);

    _String(bool v);

    _String(float v);

    _String(double v);

    _String(long v);

    template <typename T>
    void split(String v,T t);

    ~_String();

    const char * toChars();

    char charAt(int index);

    String subString(int start,int end);

    bool contains(String val);

    String trim();

    int size();

    int indexOf(String v);

    void append(String s);

    void append(const char *p);

    Integer toInteger();

    Boolean toBoolean();

    Float toFloat();

    Double toDouble();

    int toBasicInt();

    bool toBasicBool();

    float toBasicFloat();

    double toBasicDouble();

    static String valueOf(Integer v);

    static String valueOf(Boolean v);

    static String valueOf(Double v);

    static String valueOf(Float v);

    static String valueOf(int v);

    static String valueOf(bool v);

    static String valueOf(double v);

    static String valueOf(float v);

    static String valueOf(char *p);

    bool equals(String s);

    bool equals(std::string s);

    bool equals(const char *s);

    std::string getStdString();

    String toLowerCase();

    String toUpperCase();

    bool equalsIgnoreCase(String str);

    bool indexOfIgnoreCase(String str);

    bool containsIgnoreCase(String val);

    bool isEmpty();

    bool matches(String regex);
    
    sp<_String> replaceFirst(String regex,String v);

    sp<_String> replaceAll(String regex,String v);

    bool endsWith(String s);

    int lastIndexOf(String v);

    bool startsWith(String v);

private:
    std::string *m_str;
};

template <typename T>
void _String::split(String v,T t) {
    int index = 0;
    int last = 0;
    index = m_str->find_first_of(*v->m_str,last);
    while(index != std::string::npos) {
        std::string *str = new std::string(m_str->substr(last,index-last));
        t->add(createString(str));
        last = index+1;
        index = m_str->find_first_of(*v->m_str,last);
    }
    
    if(last - m_str->size() > 0){
        //ret->push_back(s.substr(last,index-last));
        std::string *str = new std::string(m_str->substr(last,index-last));
        t->add(createString(str));
    }
}

}
#endif