#ifndef __OBOTCHA_HTTP_ALLOW_METHODS_HPP__
#define __OBOTCHA_HTTP_ALLOW_METHODS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAllow) {

public:
    _HttpAllow();
    _HttpAllow(String);

    void import(String);

    void add(int);

    ArrayList<Integer> get();

    String toString();

private:
    ArrayList<Integer> methods;
};

}
#endif
