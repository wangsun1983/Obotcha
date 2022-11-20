#ifndef __OBOTCHA_HTTP_CROSS_RESOURCE_EMBEDDER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_RESOURCE_EMBEDDER_POLICY_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderCrossOriginResourcePolicy) {

public:
    _HttpHeaderCrossOriginResourcePolicy();
    _HttpHeaderCrossOriginResourcePolicy(String);

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
