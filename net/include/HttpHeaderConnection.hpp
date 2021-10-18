#ifndef __OBOTCHA_HTTP_HEADER_CONNECTION_HPP__
#define __OBOTCHA_HTTP_HEADER_CONNECTION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderConnection) {

public:
    _HttpHeaderConnection();
    _HttpHeaderConnection(String);

    void import(String);

    void set(String);

    String get();

    String toString();

private:
    String type;
};

}
#endif
