#ifndef __OBOTCHA_BOOLEAN_HPP__
#define __OBOTCHA_BOOLEAN_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Boolean) {
public:
    static const int __isReflected = 1;

    _Boolean();
    
    _Boolean(bool v);

    _Boolean(const Boolean &v);

    _Boolean(sp<_String>);

    _Boolean(const char *);

    bool toValue();

    bool equals(const Boolean &p);

    bool equals(bool p);

    bool equals(const _Boolean *p);

    void update(bool v);

    void update(const sp<_Boolean> v);

    sp<_String> toString();

    bool logicOr(bool);

    bool logicOr(const sp<_Boolean>);

    bool logicAnd(bool);

    bool logicAnd(const sp<_Boolean>);

    uint64_t hashcode();

    static sp<_Boolean> parse(const sp<_String>);

    static sp<_Boolean> parse(const char *);

    static sp<_Boolean> parse(bool);

    static const sp<_Boolean> False;

    static const sp<_Boolean> True;

    static const sp<_String> FalseString;

    static const sp<_String> TrueString;

    static sp<_String> className();

    ~_Boolean();

private:
    bool val;

    static int _parse( sp<_String>);

};

}

#endif
