#ifndef __OBOTCHA_WEB_SOCKET_HYBI07_COMPOSER_HPP__
#define __OBOTCHA_WEB_SOCKET_HYBI07_COMPOSER_HPP__

#include "Object.hpp"
#include "WebSocketHybi08Composer.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketHybi07Composer) IMPLEMENTS(WebSocketHybi08Composer){
public:
    explicit _WebSocketHybi07Composer(int type,int ver = 7,int max = kMaxWebSocketFrameSize);
};

}
#endif
