#ifndef __WEB_SOCKET_HYBI00_COMPOSER_HPP__
#define __WEB_SOCKET_HYBI00_COMPOSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"
#include "ByteArrayReader.hpp"
#include "HttpHeader.hpp"
#include "WebSocketComposer.hpp"

namespace obotcha {


DECLARE_SIMPLE_CLASS(WebSocketHybi00Composer) IMPLEMENTS(WebSocketComposer) {
public:
    String genShakeHandMessage();
};

}
#endif
