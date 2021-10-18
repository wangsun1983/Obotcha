#ifndef __OBOTCHA_HTTP_AGE_HPP__
#define __OBOTCHA_HTTP_AGE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAge) {

public:
    _HttpAge();
    _HttpAge(String);

    void import(String);

    int get();
    void set(int);
    
    String toString();

private:
    int age;
};

}
#endif
