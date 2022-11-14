#include "WebSocketHybi07Composer.hpp"

namespace obotcha {
_WebSocketHybi07Composer::_WebSocketHybi07Composer(int type,int ver,int maxframe):_WebSocketHybi08Composer(type,ver,maxframe),
                                                             _WebSocketHybi13Composer(type,ver,maxframe),
                                                             _WebSocketComposer(type,ver,maxframe) {

}

}

