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

    String get();
    void set(String);
    
    String toString();
    static const String UnSafeNone;
    static const String RequireCorp;
    
private:
    String policy;
};

}
#endif
