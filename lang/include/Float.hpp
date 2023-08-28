#ifndef __OBOTCHA_FLOAT_HPP__
#define __OBOTCHA_FLOAT_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Float) {

public:
    static const int __isReflected = 1;

    _Float() = default;

    explicit _Float(float v);

    explicit _Float(const Float & v);

    float toValue() const;

    bool equals(Object p) override;

    bool sameAs(float v) const;

    void update(float v);

    void update(sp<_Float> v);

    uint64_t hashcode() const override;

    sp<_String> toString() override;

    /**
     * the value 0 if this.val is numerically equal to value; 
     * a value less than 0 if this.val is numerically less than code value; 
     * and a value greater than 0 if this.val is numerically greater than value.
     * */
    int compareTo(float value);

    ~_Float() override = default;

    static sp<_Float> Parse(sp<_String>);

    static sp<_String> ClassName();

    /**
     * the value 0 if f1 is numerically equal to f2; 
     * a value less than 0 if f1 is numerically less than code f2; 
     * and a value greater than 0 if f1 is numerically greater than f2.
     * */
    static int Compare(float f1,float f2);

    static const float kMaxValue;
    static const float kMinValue;

private:
    float val = 0.0;
};

} // namespace obotcha
#endif