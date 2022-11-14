#ifndef __OBOTCHA_HTTP_ALLOW_METHODS_HPP__
#define __OBOTCHA_HTTP_ALLOW_METHODS_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAllow) {

public:
    _HttpHeaderAllow();
    _HttpHeaderAllow(String);

    void import(String);

    void add(int);

    ArrayList<Integer> get();

    String toString();

private:
    ArrayList<Integer> methods;
};

}
#endif
