#ifndef __OBOTCHA_HTTP_SEC_WEBSOCKET_PROTOCOL_HPP__
#define __OBOTCHA_HTTP_SEC_WEBSOCKET_PROTOCOL_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSecWebSocketProtocol) {

public:
    _HttpHeaderSecWebSocketProtocol() = default;
    explicit _HttpHeaderSecWebSocketProtocol(String);

    void load(String);

    ArrayList<String> get() const;
    String get(int) const;
    void add(String);
    void set(ArrayList<String>);

    String toString() override;

private:
    ArrayList<String> protocols = createArrayList<String>();
};

}
#endif
