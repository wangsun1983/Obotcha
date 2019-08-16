#ifndef __HTTP_URL_PARSER_HPP__
#define __HTTP_URL_PARSER_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpUrlParser) {

public:
    static HttpUrl parseUrl(String);

private:
    static void parseQuery(HttpUrl,String);
};

}

#endif
