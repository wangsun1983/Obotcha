#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_PROTOCOL_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_PROTOCOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSecWebSocketProtocol) {

public:
    _HttpSecWebSocketProtocol();
    _HttpSecWebSocketProtocol(String);

    void import(String);

    ArrayList<String> get();
    void add(String);
    void set(ArrayList<String>);

    String toString();

private:
    ArrayList<String> protocols;
};

}
#endif
