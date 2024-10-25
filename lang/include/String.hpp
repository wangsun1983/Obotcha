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

#define S(x) String::New(x)

DECLARE_CLASS(String) {
public:
    static const int __isReflected = 1;

    _String() = default;
    
    ~_String() override = default;

    explicit _String(std::string * v);

    explicit _String(const std::string v);

    explicit _String(const String &v);

    _String(const char *v);

    explicit _String(const char *v, size_t start, size_t length);

    explicit _String(const Integer &v);

    explicit _String(const Boolean &v);

    /**
     * 
     * example for precision:
     * 1.123 => precision is 4
     * 1.1 => precision is 2
     * 
    */
    _String(const Float &v, int precision = 16);

    _String(const Double &v, int precision = 16);

    explicit _String(const Long &v);

    explicit _String(const Uint8 &v);

    explicit _String(const Uint16 &v);

    explicit _String(const Uint32 &v);

    explicit _String(const Uint64 &v);

    explicit _String(const Byte &v);

    explicit _String(int v);

    explicit _String(unsigned char *v);

    explicit _String(bool v);

    explicit _String(float v, int precision = 16);

    explicit _String(double v, int precision = 16);

    explicit _String(long v);

    explicit _String(char v);

    explicit _String(uint8_t);

    explicit _String(uint16_t);

    explicit _String(uint32_t);

    explicit _String(uint64_t);

    void update(const char *);

    void update(const sp<_String> &str);

    void update(const std::string &str);

    const char *toChars() const;

    //used for some class's template(JsonVale...)
    const char *toValue() const;

    char charAt(size_t index);

    String subString(size_t start, size_t length) const;

    String trim() const;

    String trimAll() const;

    size_t size() const;

    Integer toInteger();

    Integer toHexInt();

    Integer toOctInt();

    Integer toBinaryInt();

    String toString() override;

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

    bool regionMatches(size_t toffset, String other, size_t ooffset,size_t len);

    bool regionMatchesIgnoreCase(size_t toffset, String other, size_t ooffset,size_t len);

    byte toBasicByte();

    uint64_t hashcode() const override;

    bool toBasicBool();

    float toBasicFloat();

    double toBasicDouble();

    uint8_t toBasicUint8();

    uint16_t toBasicUint16();

    uint32_t toBasicUint32();

    uint64_t toBasicUint64();

    long toBasicLong();

    ByteArray toByteArray() const;

    sp<_String> clone();

    std::string getStdString() const;

    String toLowerCase() const;

    String toUpperCase() const;

    bool contains(const String &val) const;

    bool contains(const char *val) const;

    size_t indexOf(const String &v) const;

    size_t indexOf(const char *v) const;

    size_t indexOf(char v) const;

    template <class... T> String append(T... args);

    bool equals(Object s) override;

    bool sameAs(const char *s) const;

    bool sameAs(const std::string_view s) const;

    bool sameAs(const sp<_String>) const;

    bool equalsIgnoreCase(const String &str) const;

    bool equalsIgnoreCase(const char *str, size_t size = 0) const;

    bool equalsIgnoreCase(const std::string &str) const;

    size_t indexOfIgnoreCase(const String &str) const;

    size_t indexOfIgnoreCase(const char *str) const;

    size_t indexOfIgnoreCase(const char *str, size_t size) const;

    size_t indexOfIgnoreCase(const std::string &str) const;

    bool containsIgnoreCase(const String &val) const;

    bool containsIgnoreCase(const char *str) const;

    bool containsIgnoreCase(const std::string &str) const;

    bool startsWithIgnoreCase(const String &str) const;

    bool startsWithIgnoreCase(const char *str) const;

    bool startsWithIgnoreCase(const std::string &str) const;

    bool endsWithIgnoreCase(const String &s) const;

    bool endsWithIgnoreCase(const char *str) const;

    bool endsWithIgnoreCase(const char *str, size_t size) const;

    bool endsWithIgnoreCase(const std::string &str) const;

    size_t lastIndexOfIgnoreCase(const String &v) const;

    size_t lastIndexOfIgnoreCase(const char *v) const;

    size_t lastIndexOfIgnoreCase(const char *v, size_t size) const;

    size_t lastIndexOfIgnoreCase(const std::string &str) const;

    sp<_String> replaceFirst(const String &regex, const String &v);

    sp<_String> replaceAll(const String &regex, const String &v);

    bool endsWith(const String &s) const;

    bool endsWith(const char *s,size_t size = 0) const;

    bool endsWith(const std::string &s) const;

    size_t lastIndexOf(const String &v) const;

    size_t lastIndexOf(const char *v) const;

    size_t lastIndexOf(const std::string &v) const;

    bool startsWith(const String &v) const;

    bool startsWith(const char *v) const;

    bool startsWith(const std::string &v) const;

    sp<_ArrayList<String>> split(const String &v) const;

    sp<_ArrayList<String>> split(const char *v) const;

    sp<_ArrayList<String>> split(const char *v, size_t size) const;

    size_t counts(String) const;

    //find
    size_t find(String,size_t start = 0) const;

    bool isEmpty() const;

    bool matches(const String &regex) const; // Not Test

    template<class... Args>
    static String Format(const char *fmt, Args... args) {
        int length = kFormatBuffLength;
        ByteArray data = nullptr;
        while(true) {
            data = ByteArray::New(length);
            int len = snprintf((char *)data->toValue(),length,fmt,args...);
            if(len >= length) {
                length = len + 1; //must contains a '\0'
                continue;
            }
            break;
        }

        return data->toString();
    }

    static String ClassName();

    static bool Equals(sp<_String>,sp<_String>);

    static bool EqualsIgnoreCase(const char *, const char *, size_t len = 0);

private:
    std::string m_str;

    void autoAdjustFloatString();

    // local function
    template <typename... Args>
    void _append(const sp<_String> &v, Args... args);

    template <typename... Args> void _append(const char *v, Args... args);
    template <typename... Args> void _append(std::string &v, Args... args);

    void _append();

    static String _format(const char *fmt, va_list args);

    const static uint8_t IgnoreCaseTable[128];
    const static uint8_t toLowCaseTable[128];
    const static uint8_t toUpCaseTable[128];
    const static int kFormatBuffLength = 512;
    const static std::string kFalse;
    const static std::string kTrue;
};

template <class... Args> sp<_String> _String::append(Args... args) {
    String str = String::New(m_str);
    str->_append(args...);
    return str;
}

template <class... Args>
void _String::_append(const sp<_String> &v, Args... args) {
    if (v != nullptr) {
        m_str.append(v->m_str);
        _append(args...);
    }
}

template <class... Args> void _String::_append(const char *v, Args... args) {
    if (v != nullptr) {
        m_str.append(v);
        _append(args...);
    }
}

template <class... Args> void _String::_append(std::string &v, Args... args) {
        m_str.append(v);
        _append(args...);
}

} // namespace obotcha
#endif
