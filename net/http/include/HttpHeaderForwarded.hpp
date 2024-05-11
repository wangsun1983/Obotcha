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

    String toString() override;
    String byIdentity;
    ArrayList<String> forIdentities = ArrayList<String>::New();
    String host;
    String proto;
};

}
#endif
