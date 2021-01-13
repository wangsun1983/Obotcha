#ifndef __OBOTCHA_STRING_HPP__
#define __OBOTCHA_STRING_HPP__

#include <string>
#include <iostream>
#include <stdarg.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Boolean.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "Uint8.hpp"
#include "Uint16.hpp"
#include "Uint32.hpp"
#include "Uint64.hpp"
#include "Byte.hpp"

namespace obotcha {

template<typename T>
class _ArrayList;

DECLARE_SIMPLE_CLASS(String) {
public:
    _String();

    _String(std::string *v);

    _String(const std::string v);

    _String(String v);

    _String(const char *v);

    _String(const char *v,int start,int length);

    _String(Integer &v);

    _String(Boolean &v);

    _String(Float &v);

    _String(Double &v);

    _String(Long &v);

    _String(Uint8 &v);

    _String(Uint16 &v);

    _String(Uint32 &v);

    _String(Uint64 &v);

    _String(Byte &v);

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

    void update(const char *);

    void update(sp<_String>);

    void update(std::string);

    const char * toChars();

    char charAt(int index);

    String subString(int start,int end);

    String trim();

    String trimAll();

    int size();

    Integer toInteger();

    Byte toByte();

    Boolean toBoolean();

    Float toFloat();

    Double toDouble();

    Long toLong();

    Uint8 toUint8();

    Uint16 toUint16();

    Uint32 toUint32();

    Uint64 toUint64();    

    int toBasicInt();

    byte toBasicByte();

    //TODO Remove
    int toHexInt();
    //TODO Remove
    String toHexString();

    bool toBasicBool();

    float toBasicFloat();

    double toBasicDouble();

    uint8_t toBasicUint8();

    uint16_t toBasicUint16();

    uint32_t toBasicUint32();

    uint64_t toBasicUint64();

    long toBasicLong();

    static String valueOf(Integer &v);

    static String valueOf(Boolean &v);

    static String valueOf(Double &v);

    static String valueOf(Float &v);

    static String valueOf(Long &v);

    static String valueOf(Uint8 &v);

    static String valueOf(Uint16 &v);

    static String valueOf(Uint32 &v);

    static String valueOf(Uint64 &v);

    static String valueOf(int v);

    static String valueOf(bool v);

    static String valueOf(double v);

    static String valueOf(float v);

    static String valueOf(std::uint16_t);

    static String valueOf(std::uint32_t);

    static String valueOf(std::uint64_t);

    static String valueOf(const char *p);

    static String format(const char *fmt, ...);

    static String className();

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

    int indexOf(char v);
    //----------------------------
    template<class ...T>
    String append(T...args);
    //----------------------------
    bool equals(String s);

    bool equals(std::string s);

    bool equals(const char *s);
    //----------------------------
    bool equalsIgnoreCase(String str);

    bool equalsIgnoreCase(std::string str);

    bool equalsIgnoreCase(const char * str);

    bool equalsIgnoreCase(const char * str,int csize);

    //----------------------------
    int indexOfIgnoreCase(String str);

    int indexOfIgnoreCase(std::string str);

    int indexOfIgnoreCase(const char * str);

    int indexOfIgnoreCase(const char * str,int size);

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

    bool endsWithIgnoreCase(const char * str,int size);
    //----------------------------
    int lastIndexOfIgnoreCase(String v);

    int lastIndexOfIgnoreCase(std::string v);

    int lastIndexOfIgnoreCase(const char * v);

    int lastIndexOfIgnoreCase(const char * v,int size);
    //----------------------------
    sp<_String> replaceFirst(String regex,String v);

    sp<_String> replaceFirst(const char *regex,const char*v);

    sp<_String> replaceFirst(std::string regex,std::string v);
    //----------------------------
    sp<_String> replaceAll(String regex,String v);

    sp<_String> replaceAll(const char* regex,const char* v);

    sp<_String> replaceAll(std::string regex,std::string v);
    //----------------------------
    bool endsWith(String s);

    bool endsWith(const char *s);

    bool endsWith(std::string s);
    //----------------------------
    int lastIndexOf(String v);

    int lastIndexOf(const char * v);

    int lastIndexOf(std::string v);
    //----------------------------
    bool startsWith(String v);

    bool startsWith(const char * v);

    bool startsWith(std::string v);
    //----------------------------
    sp<_ArrayList<String>> split(String v);

    sp<_ArrayList<String>> split(const char* v);

    sp<_ArrayList<String>> split(const char* v,int size);

    sp<_ArrayList<String>> split(std::string v);
    //----------------------------

    bool isEmpty();

    bool matches(String regex);//Not Test

    ~_String();

private:
    std::string m_str;

    bool isIntNumber(const char *p,int size);

    bool isDoubleNumber(const char *p,int size);

    bool isFloatNumber(const char *p,int size);

    bool isLongNumber(const char *p,int size);

    void checkParam(String &);

    //local function
    template<typename... Args>
    void _append(sp<_String> v,Args...args);

    template<typename... Args>
    void _append(const char *v,Args...args);

    template<typename... Args>
    void _append(std::string,Args...args);

    void _append();

    static String _format(const char *fmt,va_list args);

    const static  unsigned char IgnoreCaseTable[128];
    const static  unsigned char toLowCaseTable[128];
    const static  int FormatBuffLength;

    const static std::string False;
    const static std::string True;
};

template<class ...Args>
sp<_String> _String::append(Args... args) {
    String str = createString(m_str);
    str->_append(args...);
    return str;
}

template<class ...Args>
void _String::_append(sp<_String> v,Args... args) {
    if(v != nullptr) {
        m_str.append(v->m_str);
        _append(args...);
    }
}

template<class ...Args>
void _String::_append(const char *v,Args... args) {
    if(v != nullptr) {
        m_str.append(v);
        _append(args...);
    }
}

template<class ...Args>
void _String::_append(std::string v,Args... args) {
    m_str.append(v);
    _append(args...);
}

}
#endif