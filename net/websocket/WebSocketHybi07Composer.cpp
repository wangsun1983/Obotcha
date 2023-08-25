#include "WebSocketHybi07Composer.hpp"

namespace obotcha {
_WebSocketHybi07Composer::_WebSocketHybi07Composer(_WebSocketProtocol::Model model,int ver,int maxframe):_WebSocketHybi08Composer(model,ver,maxframe),
                                                             _WebSocketHybi13Composer(model,ver,maxframe),
                                                             _WebSocketComposer(model,ver,maxframe) {

}

}

