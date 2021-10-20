#ifndef __OBOTCHA_HTTP_ACCEPT_CONTROL_ALLOW_HEADERS_HPP__
#define __OBOTCHA_HTTP_ACCEPT_CONTROL_ALLOW_HEADERS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAccessControlAllowHeaders) {

public:
    _HttpAccessControlAllowHeaders();
    _HttpAccessControlAllowHeaders(String);

    void import(String);

    ArrayList<String> get();
    void add(String);

    String toString();

private:
    ArrayList<String> allowedHeaders;
};

}
#endif
