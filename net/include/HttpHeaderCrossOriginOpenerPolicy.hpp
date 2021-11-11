#ifndef __OBOTCHA_HTTP_CROSS_ORIGIN_OPENER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_ORIGIN_OPENER_POLICY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

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

private:
    int policy;
};

}
#endif
