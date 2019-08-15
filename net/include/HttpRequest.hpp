#ifndef __HTTP_REQUEST_HPP__
#define __HTTP_REQUEST_HPP__

#include <map>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpDate.hpp"
#include "DateTime.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequest) {

public:
    _HttpRequest();
    

private:
   HttpHeader mHttpHeader;

};

}

#endif
