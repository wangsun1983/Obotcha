#ifndef __OBOTCHA_HTTP_FORWARDED_HPP__
#define __OBOTCHA_HTTP_FORWARDED_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderForwarded) {

public:
    _HttpHeaderForwarded() = default;
    explicit _HttpHeaderForwarded(String);

    void load(String);

    String toString();
    String byIdentity;
    ArrayList<String> forIdentities = createArrayList<String>();
    String host;
    String proto;
};

}
#endif
