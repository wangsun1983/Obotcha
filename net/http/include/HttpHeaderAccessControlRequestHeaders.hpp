#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_HEADERS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_HEADERS_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAccessControlRequestHeaders) {

public:
    _HttpHeaderAccessControlRequestHeaders() = default;
    explicit _HttpHeaderAccessControlRequestHeaders(String);

    void load(String);

    void add(String);

    ArrayList<String> get() const;

    String toString() override;

private:
    ArrayList<String> headers = ArrayList<String>::New();
};

}
#endif
