#ifndef __OBOTCHA_HTTP_PROTOCOL_HPP__
#define __OBOTCHA_HTTP_PROTOCOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpProtocol) {
public:
    enum ProtocolType {
        HttpRequest = 0,
        HttpResponse,
    };
};

}
#endif
