#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_CONTROL_ALLOW_HEADERS_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_CONTROL_ALLOW_HEADERS_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlAllowHeaders) {

public:
    _HttpHeaderAccessControlAllowHeaders() = default;
    explicit _HttpHeaderAccessControlAllowHeaders(String);

    void load(String);

    ArrayList<String> get();
    void add(String);

    String toString() override;

private:
    ArrayList<String> allowedHeaders = ArrayList<String>::New();
};

}
#endif
