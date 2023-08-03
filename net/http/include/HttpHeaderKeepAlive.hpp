#ifndef __OBOTCHA_HTTP_HEADER_KEEP_ALIVE_HPP__
#define __OBOTCHA_HTTP_HEADER_KEEP_ALIVE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderKeepAlive) {

public:
    _HttpHeaderKeepAlive() = default;
    explicit _HttpHeaderKeepAlive(String);

    void load(String);
    int getTimeout() const;
    int getMax() const;

    void setTimeout(int);
    void setMax(int);

    String toString() override;

private:
    int timeout = -1; //time for idle status (seconds)
    int max = -1; //max request nums before connection closed
};

}
#endif
