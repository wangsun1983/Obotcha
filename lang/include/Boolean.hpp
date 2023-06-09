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
    
    void update(const sp<_Boolean> &v);
    
    sp<_String> toString();
    
    bool logicOr(bool value);
    
    bool logicOr(const sp<_Boolean>& value);
    
    bool logicAnd(bool value);
    
    bool logicAnd(const sp<_Boolean>& value);
    
    bool logicXor(bool value);
    
    bool logicXor(const sp<_Boolean>& value);
    
    uint64_t hashcode();

    static sp<_Boolean> Parse(const sp<_String> & value);
    static sp<_Boolean> Parse(const char *);
    static sp<_String> ClassName();

    ~_Boolean();

private:
    bool val;

    static int _parse(sp<_String>);

    static const int kTrueValue;
    static const int kFalseValue;
    static const int kInValidValue;
    static const char *kTrueString;
    static const char *kFalseString;
};

} // namespace obotcha

#endif
