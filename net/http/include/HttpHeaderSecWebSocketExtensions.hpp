#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_EXTENSIONS_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_EXTENSIONS_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketExtensions) {

public:
    _HttpHeaderSecWebSocketExtensions() = default;
    explicit _HttpHeaderSecWebSocketExtensions(String);

    void load(String);

    ArrayList<String> get() const;
    void set(ArrayList<String>);
    void add(String);

    String toString() override;

private:
    ArrayList<String> extensions = ArrayList<String>::New();
};

}
#endif
