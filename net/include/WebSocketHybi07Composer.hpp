#ifndef __WEB_SOCKET_HYBI07_COMPOSER_HPP__
#define __WEB_SOCKET_HYBI07_COMPOSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi08Composer.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketHybi07Composer) IMPLEMENTS(WebSocketHybi08Composer){
public:
    _WebSocketHybi07Composer(int,int max = MAX_WEBSOCKET_FRAME_SIZE);
};

}
#endif
