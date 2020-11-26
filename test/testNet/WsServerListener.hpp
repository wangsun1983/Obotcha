#include <stdio.h>
#include <unistd.h>

#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketServer.hpp"
#include "WebSocketListener.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoLock.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketComposer.hpp"
#include "File.hpp"
#include "FileOutputStream.hpp"
#include "Atomic.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(WsServerListener) IMPLEMENTS(WebSocketListener) {
public:
    _WsServerListener();

    int onMessage(sp<_WebSocketClientInfo> client,WebSocketFrame frame);

    int onData(sp<_WebSocketClientInfo> client,WebSocketFrame frame);

    int onConnect(sp<_WebSocketClientInfo> client);

    int onDisconnect(sp<_WebSocketClientInfo> client);

    int onPong(sp<_WebSocketClientInfo> client,String);

    int onPing(sp<_WebSocketClientInfo> client,String);

private:
    Atomic<int> mConnectCounts;
    Atomic<int> mDisconnectCounts;
    Atomic<long> mRcvDataSize;
};