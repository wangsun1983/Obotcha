#ifndef __OBOTCHA_HTTP_HEADER_HOST_HPP__
#define __OBOTCHA_HTTP_HEADER_HOST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderHost) {

public:
    _HttpHeaderHost();
    _HttpHeaderHost(String);

    void import(String);

    void setHost(String);
    void setPort(int);

    String getHost();
    int getPort();

    String toString();

private:
    String host;
    int port;
};

}
#endif
