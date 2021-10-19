#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_EXPOSE_HEADERS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_EXPOSE_HEADERS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

/*
* only the following header can be exposed
* =========================================
* Cache-Control
* Content-Language
* Content-Length
* Content-Type
* Expires
* Last-Modified
* Pragma
*/
DECLARE_CLASS(HttpAccessControlExposeHeaders) {

public:
    _HttpAccessControlExposeHeaders();
    _HttpAccessControlExposeHeaders(String);

    void import(String);

    void addHeaders(String);

    ArrayList<String> getHeaders();

    String toString();

private:
    ArrayList<String> headers;
};

}
#endif
