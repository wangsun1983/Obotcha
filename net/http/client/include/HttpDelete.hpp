#ifndef __OBOTCHA_HTTP_DELETE_HPP__
#define __OBOTCHA_HTTP_DELETE_HPP__

#include "Object.hpp"
#include "HttpRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpDelete) IMPLEMENTS(HttpRequest) {
public:
    explicit _HttpDelete(String url);

    String getMethodName() const;
};

}

#endif