#ifndef __OBOTCHA_HTTP_AGE_HPP__
#define __OBOTCHA_HTTP_AGE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAge) {

public:
    _HttpHeaderAge() = default;
    explicit _HttpHeaderAge(String);

    void load(String);

    int get();
    void set(int);
    
    String toString();

private:
    int age;
};

}
#endif
