#ifndef __OBOTCHA_HTTP_HEADER_REFERRER_POLICY_HPP__
#define __OBOTCHA_HTTP_HEADER_REFERRER_POLICY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderReferrerPolicy) {

public:
    _HttpHeaderReferrerPolicy();
    _HttpHeaderReferrerPolicy(String);

    void import(String);
    
    ArrayList<String> get();
    void set(ArrayList<String>);
    void add(String);

    String toString();

private:
    ArrayList<String> policies;
};

}
#endif