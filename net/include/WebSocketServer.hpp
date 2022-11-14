#ifndef __OBOTCHA_WEBSOCKET_SERVER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_HPP__

#include "Object.hpp"

#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "SocketListener.hpp"
#include "String.hpp"
#include "WebSocketLinker.hpp"
#include "WebSocketListener.hpp"
#include "WebSocketOption.hpp"
#include "ConcurrentHashMap.hpp"

namespace obotcha {

class _WebSocketServerBuilder;

//------------------------WebSocketServer-------------------------
DECLARE_CLASS(WebSocketServer) IMPLEMENTS(HttpListener, SocketListener) {
public:
    friend class _WebSocketServerBuilder;

    _WebSocketServer(int threadnum);

    int start();

    int close();

    void dump();

    int bind(String, WebSocketListener);

private:
    void onHttpMessage(int, sp<_HttpLinker> client, HttpResponseWriter w,
                       HttpPacket msg);

    void onSocketMessage(int, Socket, ByteArray);

    WebSocketLinker createLinker(sp<_HttpLinker>,int ver);

    InetAddress mAddress;

    HttpServer mHttpServer;

    SocketMonitor mSocketMonitor;

    HashMap<String, WebSocketListener> mWsListeners;

    WebSocketOption mWsOption;

    HttpOption mHttpOption;

    //WebSocketLinkerManager mLinkerManager;
    ConcurrentHashMap<Socket,sp<_WebSocketLinker>> mLinkers;
};

} // namespace obotcha
#endif
