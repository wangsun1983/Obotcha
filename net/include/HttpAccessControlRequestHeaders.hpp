#ifndef __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_HEADERS_HPP__
#define __OBOTCHA_HTTP_ACCESS_CONTROL_REQUEST_HEADERS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAccessCrontrolRequestHeaders) {

public:
    _HttpAccessCrontrolRequestHeaders();
    _HttpAccessCrontrolRequestHeaders(String);

    void import(String);

    void addHeaders(String);

    ArrayList<String> getHeaders();

    String toString();

private:
    ArrayList<String> headers;
};

}
#endif
