#ifndef __OBOTCHA_HTTP_HEADER_SEC_FETCH_USER_HPP__
#define __OBOTCHA_HTTP_HEADER_SEC_FETCH_USER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecFetchUser) {

public:
    _HttpHeaderSecFetchUser();
    _HttpHeaderSecFetchUser(String);

    void import(String);

    void set(String);

    String get();

    String toString();

    const static String UserActivate;
    const static String OtherActivate;

private:
    String value;
};

}
#endif
