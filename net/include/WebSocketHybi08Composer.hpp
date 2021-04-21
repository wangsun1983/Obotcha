#ifndef __OBOTCHA_WEB_SOCKET_HYBI08_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI08_COMPOSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketParser.hpp"
#include "WebSocketHybi13Composer.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 08
/**
 * The primary difference between 08 and 13 is a different origin header name
 */
DECLARE_SIMPLE_CLASS(WebSocketHybi08Composer) IMPLEMENTS(WebSocketHybi13Composer){
public:
    _WebSocketHybi08Composer(int type,int ver = 8,int max = MAX_WEBSOCKET_FRAME_SIZE);

};

}
#endif
