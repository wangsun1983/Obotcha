#ifndef __OBOTCHA_HTTP_HEADER_HOST_HPP__
#define __OBOTCHA_HTTP_HEADER_HOST_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderHost) {

public:
    _HttpHeaderHost() = default;
    _HttpHeaderHost(String,int);

    void load(String);

    void setHost(String);
    void setPort(int);

    String getHost() const;
    int getPort() const;

    String toString() override;

private:
    String host = nullptr;
    int port = -1;
};

}
#endif
