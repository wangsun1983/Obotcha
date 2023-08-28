#ifndef __OBOTCHA_DOUBLE_HPP__
#define __OBOTCHA_DOUBLE_HPP__

#include "Object.hpp"

namespace obotcha {

class _String;

DECLARE_CLASS(Double) {
public:
    static const int __isReflected = 1;

    _Double() = default;

    explicit _Double(double v);

    explicit _Double(const Double &v);

    double toValue() const;

    void update(double);

    void update(const sp<_Double> &);

    bool equals(Object p) override;

    bool sameAs(double p) const;
    
    sp<_String> toString() override;

    uint64_t hashcode() const override;

    ~_Double() override = default;

    /**
     * the value 0 if this.val is numerically equal to value; 
     * a value less than 0 if this.val is numerically less than code value; 
     * and a value greater than 0 if this.val is numerically greater than value.
     * */
    int compareTo(double value);

    static sp<_Double> Parse(sp<_String>);

    /**
     * the value 0 if f1 is numerically equal to f2; 
     * a value less than 0 if f1 is numerically less than code f2; 
     * and a value greater than 0 if f1 is numerically greater than f2.
     * */
    static int Compare(double f1,double f2);

    static sp<_String> ClassName();

    static const double kMaxValue;
    static const double kMinValue;

private:
    double mValue = 0.0;
};

} // namespace obotcha
#endif
