#ifndef __OBOTCHA_HTTP_CONNECTION_LISTENER_HPP__
#define __OBOTCHA_HTTP_CONNECTION_LISTENER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpResponse.hpp"

namespace obotcha {

DECLARE_CLASS(HttpConnectionListener) {
public:
    virtual void onResponse(HttpResponse response) = 0;
    virtual void onDisconnect() = 0;
};

}
#endif
