#ifndef __OBOTCHA_HTTP_POST_HPP__
#define __OBOTCHA_HTTP_POST_HPP__

#include "Object.hpp"
#include "HttpRequest.hpp"

namespace obotcha {

DECLARE_CLASS(HttpPost) IMPLEMENTS(HttpRequest){
public:
    explicit _HttpPost(String url);

    String getMethodName() const;
};

}

#endif