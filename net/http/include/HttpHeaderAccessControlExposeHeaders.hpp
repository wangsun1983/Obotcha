#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_EXPOSE_HEADERS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_EXPOSE_HEADERS_HPP__

#include "Object.hpp"
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
DECLARE_CLASS(HttpHeaderAccessControlExposeHeaders) {

public:
    _HttpHeaderAccessControlExposeHeaders() = default;
    explicit _HttpHeaderAccessControlExposeHeaders(String);

    void load(String);

    void add(String);

    ArrayList<String> get();

    String toString() override;

private:
    ArrayList<String> headers = createArrayList<String>();
};

}
#endif
