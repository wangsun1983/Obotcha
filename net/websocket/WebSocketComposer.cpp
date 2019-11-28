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

_WebSocketComposer::_WebSocketComposer(int v,int maxframesize) {
    mType = v;
    mMaxFrameSize = maxframesize;
}

int _WebSocketComposer::getMaxFrameSize() {
    return mMaxFrameSize;
}

void _WebSocketComposer::setMaxFrameSzie(int v) {
    mMaxFrameSize = v;
}

}
