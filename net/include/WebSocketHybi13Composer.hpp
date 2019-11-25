#ifndef __WEB_SOCKET_HYBI13_COMPOSER_HPP__
#define __WEB_SOCKET_HYBI13_COMPOSER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketComposer.hpp"
#include "Sha.hpp"
#include "Base64.hpp"

namespace obotcha {

/// Processor for Hybi Draft version 00
/**
 * There are many differences between Hybi 00 and Hybi 13
 */
DECLARE_SIMPLE_CLASS(WebSocketHybi13Composer) IMPLEMENTS(WebSocketComposer){
public:
    _WebSocketHybi13Composer(int);
    String genShakeHandMessage(WebSocketClientInfo h);
    
private:
    String genClientShakeHandMessage(WebSocketClientInfo h);
    String genServerShakeHandMessage(WebSocketClientInfo h);

    Sha mSha;
    Base64 mBase64;
};

}
#endif
