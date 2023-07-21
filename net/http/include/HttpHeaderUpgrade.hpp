#ifndef __OBOTCHA_HTTP_HEADER_UPGRADE_HPP__
#define __OBOTCHA_HTTP_HEADER_UPGRADE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderUpgrade) {

public:
    _HttpHeaderUpgrade() = default;
    explicit _HttpHeaderUpgrade(String);

    void load(String);

    String get();
    void set(String);

    String toString();

private:
    String upgrade;
};

}
#endif
