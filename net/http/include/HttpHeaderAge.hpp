#ifndef __OBOTCHA_HTTP_AGE_HPP__
#define __OBOTCHA_HTTP_AGE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAge) {

public:
    _HttpHeaderAge();
    _HttpHeaderAge(String);

    void import(String);

    int get();
    void set(int);
    
    String toString();

private:
    int age;
};

}
#endif
