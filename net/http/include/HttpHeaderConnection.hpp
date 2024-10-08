#ifndef __OBOTCHA_HTTP_HEADER_CONNECTION_HPP__
#define __OBOTCHA_HTTP_HEADER_CONNECTION_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderConnection) {

public:
    _HttpHeaderConnection() = default;
    explicit _HttpHeaderConnection(String);
    void load(String);
    void set(String);
    String get();
    String toString() override;

private:
    String type;
};

}
#endif
