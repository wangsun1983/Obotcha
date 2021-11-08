#ifndef __OBOTCHA_HTTP_CROSS_ORIGIN_OPENER_POLICY_HPP__
#define __OBOTCHA_HTTP_CROSS_ORIGIN_OPENER_POLICY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpCrossOriginOpenerPolicy) {

public:
    _HttpCrossOriginOpenerPolicy();
    _HttpCrossOriginOpenerPolicy(String);

    void import(String);

    String get();
    void set(String);
    
    String toString();

private:
    int policy;
};

}
#endif
