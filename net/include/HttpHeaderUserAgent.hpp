#ifndef __OBOTCHA_HTTP_HEADER_USER_AGENT_HPP__
#define __OBOTCHA_HTTP_HEADER_USER_AGENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderUserAgent) {

public:
    _HttpHeaderUserAgent();
    _HttpHeaderUserAgent(String);

    void import(String);
    void set(String);
    String get();

    String toString();

private:
    String agent;
};

}
#endif
