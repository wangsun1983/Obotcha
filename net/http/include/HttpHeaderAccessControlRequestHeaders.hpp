#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_HEADERS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_HEADERS_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlRequestHeaders) {

public:
    _HttpHeaderAccessControlRequestHeaders();
    _HttpHeaderAccessControlRequestHeaders(String);

    void import(String);

    void add(String);

    ArrayList<String> get();

    String toString();

private:
    ArrayList<String> headers;
};

}
#endif