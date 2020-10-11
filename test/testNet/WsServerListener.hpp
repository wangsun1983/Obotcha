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
#include "WebSocketFrameComposer.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketComposer.hpp"
#include "File.hpp"
#include "FileOutputStream.hpp"
#include "AtomicLong.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(WsServerListener) IMPLEMENTS(WebSocketListener) {
public:
    _WsServerListener();

    int onMessage(sp<_WebSocketClientInfo> client,String message);

    int onData(sp<_WebSocketClientInfo> client,ByteArray data);

    int onConnect(sp<_WebSocketClientInfo> client);

    int onDisconnect(sp<_WebSocketClientInfo> client);

    int onPong(sp<_WebSocketClientInfo> client,String);

    int onPing(sp<_WebSocketClientInfo> client,String);

private:
    AtomicInteger mConnectCounts;
    AtomicInteger mDisconnectCounts;
    AtomicLong mRcvDataSize;
};