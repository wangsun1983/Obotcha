#ifndef __OBOTCHA_HTTP_HEADER_SERVER_HPP__
#define __OBOTCHA_HTTP_HEADER_SERVER_HPP__

//according nginx/conf/mime.types

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderServer) {

public:
    _HttpHeaderServer();
    explicit _HttpHeaderServer(String);

    void load(String value);

    String toString();

    String get();
    void set(String);

private:
    String server;
};

}
#endif
