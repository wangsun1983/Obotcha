#ifndef __OBOTCHA_STRING_HPP__
#define __OBOTCHA_STRING_HPP__

#include <iostream>
#include <stdarg.h>
#include <string>
#include <functional>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Boolean.hpp"
#include "Byte.hpp"
#include "ByteArray.hpp"
#include "Double.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Long.hpp"
#include "Uint16.hpp"
#include "Uint32.hpp"
#include "Uint64.hpp"
#include "Uint8.hpp"

namespace obotcha {

template <typename T> class _ArrayList;

#define S(x) createString(x)

DECLARE_CLASS(String) {
public:
    static const int __isReflected = 1;

    _String();

    _String(std::string * v);

    _String(const std::string v);

    _String(const String &v);

    _String(const char *v);

    _String(const char *v, int start, int length);

    _String(const Integer &v);

    _String(const Boolean &v);

    _String(const Float &v, int precision = 16);

    _String(const Double &v, int precision = 16);

    _String(const Long &v);

    _String(const Uint8 &v);

    _String(const Uint16 &v);

    _String(const Uint32 &v);

    _String(const Uint64 &v);

    _String(const Byte &v);

    _String(int v);

    _String(unsigned char *v);

    _String(bool v);

    _String(float v, int precision = 16);

    _String(double v, int precision = 16);

    _String(long v);

    _String(char v);

    _String(uint8_t);

    _String(uint16_t);

    _String(uint32_t);

    _String(uint64_t);

    void update(const char *);

    void update(const sp<_String> &str);

    void update(const std::string &str);

    const char *toChars();

    //used for some class's template(JsonVale...)
    const char *toValue();

    char charAt(int index);

    String subString(int start, int length);

    String trim();

    String trimAll();

    int size();

    Integer toInteger();

    Integer toHexInt();

    Integer toOctInt();

    Integer toBinaryInt();

    String toString();

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

    bool regionMatches(int toffset, String other, int ooffset,int len);

    bool regionMatchesIgnoreCase(int toffset, String other, int ooffset,int len);

    byte toBasicByte();

    uint64_t hashcode();

    bool toBasicBool();

    float toBasicFloat();

    double toBasicDouble();

    uint8_t toBasicUint8();

    uint16_t toBasicUint16();

    uint32_t toBasicUint32();

    uint64_t toBasicUint64();

    long toBasicLong();

    ByteArray toByteArray();

    sp<_String> clone();

    static String format(const char *fmt, ...);

    static String className();

    static bool isEquals(sp<_String>,sp<_String>);

    static bool isEqualsIgnoreCase(const char *, const char *, int len = -1);

    std::string getStdString();

    String toLowerCase();

    String toUpperCase();

    bool contains(const String &val);

    bool contains(const char *val);

    int indexOf(const String &v);

    int indexOf(const char *v);

    int indexOf(char v);

    template <class... T> String append(T... args);

    bool equals(const String &s);

    bool equals(const char *s);

    bool equals(const std::string &s);

    bool equalsIgnoreCase(const String &str);

    bool equalsIgnoreCase(const char *str, int size = -1);

    bool equalsIgnoreCase(const std::string str);

    int indexOfIgnoreCase(const String &str);

    int indexOfIgnoreCase(const char *str);

    int indexOfIgnoreCase(const char *str, int size);

    int indexOfIgnoreCase(const std::string &str);

    bool containsIgnoreCase(const String &val);

    bool containsIgnoreCase(const char *str);

    bool containsIgnoreCase(const std::string &str);

    bool startsWithIgnoreCase(const String &str);

    bool startsWithIgnoreCase(const char *str);

    bool startsWithIgnoreCase(const std::string &str);

    bool endsWithIgnoreCase(const String &s);

    bool endsWithIgnoreCase(const char *str);

    bool endsWithIgnoreCase(const char *str, int size);

    bool endsWithIgnoreCase(const std::string &str);

    int lastIndexOfIgnoreCase(const String &v);

    int lastIndexOfIgnoreCase(const char *v);

    int lastIndexOfIgnoreCase(const char *v, int size);

    int lastIndexOfIgnoreCase(const std::string &str);

    sp<_String> replaceFirst(const String &regex, const String &v);

    sp<_String> replaceAll(const String &regex, const String &v);

    bool endsWith(const String &s);

    bool endsWith(const char *s);

    bool endsWith(const std::string &s);

    int lastIndexOf(const String &v);

    int lastIndexOf(const char *v);

    int lastIndexOf(const std::string &v);

    bool startsWith(const String &v);

    bool startsWith(const char *v);

    bool startsWith(const std::string &v);

    sp<_ArrayList<String>> split(const String &v);

    sp<_ArrayList<String>> split(const char *v);

    sp<_ArrayList<String>> split(const char *v, int size);

    int counts(String);

    //find
    int find(String,int start = 0);

    bool isEmpty();

    bool matches(const String &regex); // Not Test

    ~_String();

private:
    std::string m_str;

    // local function
    template <typename... Args>
    void _append(const sp<_String> &v, Args... args);

    template <typename... Args> void _append(const char *v, Args... args);
    template <typename... Args> void _append(std::string v, Args... args);

    void _append();

    static String _format(const char *fmt, va_list args);

    const static unsigned char IgnoreCaseTable[128];
    const static unsigned char toLowCaseTable[128];
    const static unsigned char toUpCaseTable[128];
    const static int kFormatBuffLength;
    const static std::string kFalse;
    const static std::string kTrue;
};

template <class... Args> sp<_String> _String::append(Args... args) {
    String str = createString(m_str);
    str->_append(std::forward<Args>(args)...);
    return str;
}

template <class... Args>
void _String::_append(const sp<_String> &v, Args... args) {
    if (v != nullptr) {
        m_str.append(v->m_str);
        _append(std::forward<Args>(args)...);
    }
}

template <class... Args> void _String::_append(const char *v, Args... args) {
    if (v != nullptr) {
        m_str.append(v);
        _append(std::forward<Args>(args)...);
    }
}

template <class... Args> void _String::_append(std::string v, Args... args) {
        m_str.append(v);
        _append(std::forward<Args>(args)...);
}

} // namespace obotcha
#endif
