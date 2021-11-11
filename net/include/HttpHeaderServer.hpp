#ifndef __OBOTCHA_HTTP_HEADER_SERVER_HPP__
#define __OBOTCHA_HTTP_HEADER_SERVER_HPP__

//according nginx/conf/mime.types

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "HttpCookie.hpp"
#include "Mutex.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderServer) {

public:
    _HttpHeaderServer();
    _HttpHeaderServer(String);

    void import(String value);

    String toString();

    String get();
    void set(String);

private:
    String server;
};

}
#endif
