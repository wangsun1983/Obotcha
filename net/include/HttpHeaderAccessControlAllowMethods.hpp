#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_METHODS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_ALLOW_METHODS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlAllowMethods) {

public:
    _HttpHeaderAccessControlAllowMethods();
    _HttpHeaderAccessControlAllowMethods(String);

    void import(String);

    void add(int);

    ArrayList<Integer> get();

    String toString();

private:
    ArrayList<Integer> methods;
};

}
#endif
