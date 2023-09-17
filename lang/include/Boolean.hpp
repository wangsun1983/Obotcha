#ifndef __OBOTCHA_BOOLEAN_HPP__
#define __OBOTCHA_BOOLEAN_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Boolean) {
public:
    static const int __isReflected = 1;

    _Boolean();

    explicit _Boolean(bool v);
    
    explicit _Boolean(const Boolean &v);
    
    explicit _Boolean(sp<_String>);
    
    explicit _Boolean(const char *);
    
    bool toValue() const;
    
    bool equals(Object p) override;

    bool sameAs(bool) const;
    
    void update(bool v);
    
    void update(const sp<_Boolean> &v);
    
    sp<_String> toString() override;
    
    bool logicOr(bool value);
    
    bool logicOr(const sp<_Boolean>& value);
    
    bool logicAnd(bool value);
    
    bool logicAnd(const sp<_Boolean>& value);
       
    uint64_t hashcode() const override;

    static sp<_Boolean> Parse(const sp<_String> & value);
    static sp<_Boolean> Parse(const char *);
    static sp<_String> ClassName();

    ~_Boolean() override = default;

private:
    bool mValue;

    static bool _parse(sp<_String>);
    static const char *kTrueString;
    static const char *kFalseString;
};

} // namespace obotcha

#endif
