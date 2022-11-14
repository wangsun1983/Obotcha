#include "WebSocketHybi08Composer.hpp"

namespace obotcha {

_WebSocketHybi08Composer::_WebSocketHybi08Composer(int type,int ver,int maxframe):_WebSocketHybi13Composer(type,ver,maxframe),
                                                             _WebSocketComposer(type,ver,maxframe) {

}

}

