#ifndef __OBOTCHA_HTTP_HEADER_KEEP_ALIVE_HPP__
#define __OBOTCHA_HTTP_HEADER_KEEP_ALIVE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderKeepAlive) {

public:
    _HttpHeaderKeepAlive();
    _HttpHeaderKeepAlive(String);

    void import(String);
    int getTimeout();
    int getMax();

    void setTimeout(int);
    void setMax(int);

    String toString();

private:
    int timeout; //time for idle status (seconds)
    int max; //max request nums before connection closed
};

}
#endif
