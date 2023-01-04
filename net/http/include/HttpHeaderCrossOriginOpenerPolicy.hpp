#ifndef __OBOTCHA_HTTP_CROSS_ORIGIN_OPENER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_ORIGIN_OPENER_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderCrossOriginOpenerPolicy) {

public:
    _HttpHeaderCrossOriginOpenerPolicy();
    _HttpHeaderCrossOriginOpenerPolicy(String);

    void import(String);
    bool isUnSafeNone();
    bool isSameOrigin();
    bool isSameOriginAllowPopups();

    void setAsUnSafeNone();
    void setAsSameOrigin();
    void setAsSameOriginAllowPopups();
    
    String toString();
    static const String UnSafeNone;
    static const String SameOrigin;
    static const String SameOriginAllowPopups;
    
private:
    enum CoopType {
        TypeUnSafeNone = 0,
        TypeSameOrigin,
        TypeSameOriginAllowPopups,
    };

    int mType;
};

}
#endif
