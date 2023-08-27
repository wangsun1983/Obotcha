#ifndef __OBOTCHA_HTTP_ALLOW_METHODS_HPP__
#define __OBOTCHA_HTTP_ALLOW_METHODS_HPP__

#include <vector>

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpMethod.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAllow) {

public:
    _HttpHeaderAllow() = default;
    explicit _HttpHeaderAllow(String);

    void load(String);

    void add(st(HttpMethod)::Id);

    ArrayList<Integer> get();

    String toString() override;

private:
    std::vector<st(HttpMethod)::Id> methods;
};

}
#endif
