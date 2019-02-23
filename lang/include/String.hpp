#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <string>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Integer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"

using namespace std;

DECLARE_SIMPLE_CLASS(String)
{
public:
    _String();

    _String(String v);

    _String(char *v);

    _String(char *v,int start,int length);

    ~_String();

    char * toChars();

    char charAt(int index);

    String subString(int start,int end);

    bool contains(String val);

    String trim();

    int length();

    int indexOf(String v);
    
    static String valueOf(Integer v);

    static String valueOf(Boolean v);

    static String valueOf(Double v);

    static String valueOf(Float v);

    static String valueOf(char *p);

    bool equals();

private:
    std::string *m_str;
};

#endif