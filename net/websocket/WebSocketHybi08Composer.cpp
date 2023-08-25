#include "WebSocketHybi08Composer.hpp"

namespace obotcha {

_WebSocketHybi08Composer::_WebSocketHybi08Composer(_WebSocketProtocol::Model model,int ver,int maxframe):_WebSocketHybi13Composer(model,ver,maxframe),
                                                             _WebSocketComposer(model,ver,maxframe) {

}

}

