#ifndef __BOOLEAN_HPP__
#define __BOOLEAN_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _String;

DECLARE_SIMPLE_CLASS(Boolean) {
public:
    _Boolean(bool v);

    _Boolean(Boolean &v);

    bool toValue();

    bool equals(Boolean &p);

    bool equals(bool p);

    bool equals(const _Boolean *p);

    void update(bool v);

    sp<_String> toString();

    bool compareTo(sp<_Boolean>);

    void logicOr(bool);

    void logicOr(sp<_Boolean>);

    void logicAnd(bool);

    void logicAnd(sp<_Boolean>);

    void logicXor(bool);

    void logicXor(sp<_Boolean>);

    static sp<_Boolean> valueOf(sp<_String>);

    static sp<_Boolean> valueOf(char *);

    static sp<_Boolean> valueOf(bool);

    static sp<_Boolean> FALSE;

    static sp<_Boolean> TRUE;

    static sp<_String> FALSE_STRING;

    static sp<_String> TRUE_STRING;

    ~_Boolean();

private:
    bool val;

};

}

#endif
