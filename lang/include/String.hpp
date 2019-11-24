#ifndef __STRING_HPP__
#define __STRING_HPP__

#include <string>
#include <iostream>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Integer.hpp"
#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Long.hpp"
#include "Byte.hpp"
#include "Uint8.hpp"
#include "Uint16.hpp"
#include "Uint32.hpp"
#include "Uint64.hpp"

using namespace std;

namespace obotcha {

template<typename T>
class _ArrayList;

DECLARE_SIMPLE_CLASS(String) {
public:
    _String();

    _String(std::string *v);

    _String(std::string v);

    _String(String v);

    _String(const char *v);

    _String(const char *v,int start,int length);

    _String(Integer v);

    _String(Boolean v);

    _String(Float v);

    _String(Double v);

    _String(Long v);

    _String(Byte v);

    _String(Uint8);

    _String(Uint16);

    _String(Uint32);

    _String(Uint64);

    _String(int v);

    _String(bool v);

    _String(float v);

    _String(double v);

    _String(long v);

    _String(char v);

    _String(uint8_t);

    _String(uint16_t);

    _String(uint32_t);

    _String(uint64_t);

    sp<_ArrayList<String>> split(String v);

    const char * toChars();

    char charAt(int index);

    String subString(int start,int end);

    String trim();

    String trimAll();

    int size();

    Integer toInteger();

    Boolean toBoolean();

    Float toFloat();

    Double toDouble();

    Long toLong();

    Uint8 toUint8();

    Uint16 toUint16();

    Uint32 toUint32();

    Uint64 toUint64();    

    int toBasicInt();

    int toHexInt();

    bool toBasicBool();

    float toBasicFloat();

    double toBasicDouble();

    uint8_t toBasicUint8();

    uint16_t toBasicUint16();

    uint32_t toBasicUint32();

    uint64_t toBasicUint64();

    long toBasicLong();

    static String valueOf(Integer v);

    static String valueOf(Boolean v);

    static String valueOf(Double v);

    static String valueOf(Float v);

    static String valueOf(int v);

    static String valueOf(bool v);

    static String valueOf(double v);

    static String valueOf(float v);

    static String valueOf(const char *p);

    std::string getStdString();

    String toLowerCase();

    String toUpperCase();

    //need support String/std::string/char *
    //----------------------------
    bool contains(String val);

    bool contains(std::string val);
    
    bool contains(const char *val);
    //----------------------------
    int indexOf(String v);

    int indexOf(std::string v);

    int indexOf(const char *v);
    //----------------------------
    String append(String s);

    String append(std::string s);

    String append(const char *p);
    //----------------------------
    bool equals(String s);

    bool equals(std::string s);

    bool equals(const char *s);
    //----------------------------
    bool equalsIgnoreCase(String str);

    bool equalsIgnoreCase(std::string str);

    bool equalsIgnoreCase(const char * str);

    //----------------------------
    int indexOfIgnoreCase(String str);

    int indexOfIgnoreCase(std::string str);

    int indexOfIgnoreCase(const char * str);
    //----------------------------
    bool containsIgnoreCase(String val);

    bool containsIgnoreCase(std::string str);

    bool containsIgnoreCase(const char * str);
    //----------------------------
    bool startsWithIgnoreCase(String str);
    
    bool startsWithIgnoreCase(std::string str);

    bool startsWithIgnoreCase(const char * str);
    //----------------------------
    bool endsWithIgnoreCase(String s);

    bool endsWithIgnoreCase(std::string str);

    bool endsWithIgnoreCase(const char * str);
    //----------------------------
    int lastIndexOfIgnoreCase(String v);

    int lastIndexOfIgnoreCase(std::string v);

    int lastIndexOfIgnoreCase(const char * v);
    //----------------------------

    bool isEmpty();

    bool matches(String regex);//Not Test
    
    sp<_String> replaceFirst(String regex,String v);

    sp<_String> replaceAll(String regex,String v);

    bool endsWith(String s);

    int lastIndexOf(String v);

    bool startsWith(String v);

    ~_String();

private:
    std::string m_str;

    bool isIntNumber(const char *p,int size);

    bool isDoubleNumber(const char *p,int size);

    bool isFloatNumber(const char *p,int size);

    bool isLongNumber(const char *p,int size);    
};

}
#endif