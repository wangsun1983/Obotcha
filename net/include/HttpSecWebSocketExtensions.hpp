#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_EXTENSIONS_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_EXTENSIONS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpSecWebSocketExtensions) {

public:
    _HttpSecWebSocketExtensions();
    _HttpSecWebSocketExtensions(String);

    void import(String);

    ArrayList<String> get();
    void set(ArrayList<String>);
    void add(String);

    String toString();

private:
    ArrayList<String> extensions;
};

}
#endif
