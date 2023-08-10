#ifndef __OBOTCHA_WEBSOCKET_SERVER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_HPP__

#include <atomic>

#include "Object.hpp"
#include "ConcurrentHashMap.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "SocketListener.hpp"
#include "String.hpp"
#include "WebSocketLinker.hpp"
#include "WebSocketListener.hpp"
#include "WebSocketOption.hpp"
#include "ConcurrentHashMap.hpp"
#include "WebSocketInputReader.hpp"
#include "WebSocketOutputWriter.hpp"
#include "WebSocketInspector.hpp"

namespace obotcha {

//------------------------WebSocketServer-------------------------
DECLARE_CLASS(WebSocketServer) IMPLEMENTS(HttpListener, SocketListener) {
public:
    explicit _WebSocketServer(InetAddress addr = nullptr,HttpOption option = nullptr,int threadnum = 4);

    int start();

    int close();

    int bind(String, WebSocketListener);

private:
    enum Status {
        Idle = 0,
        Running,
        Closed
    };

    void onHttpMessage(st(Net)::Event, sp<_HttpLinker> client, HttpResponseWriter w,
                       HttpPacket msg);

    void onSocketMessage(st(Net)::Event, Socket, ByteArray);

    WebSocketLinker createLinker(sp<_HttpLinker>,int ver) const;

    InetAddress mAddress = nullptr;

    HttpServer mHttpServer = nullptr;

    SocketMonitor mSocketMonitor = nullptr;

    ConcurrentHashMap<String, WebSocketListener> mWsListeners = createConcurrentHashMap<String,WebSocketListener>();

    HttpOption mHttpOption = nullptr;

    ConcurrentHashMap<Socket,sp<_WebSocketLinker>> mLinkers = createConcurrentHashMap<Socket,sp<_WebSocketLinker>>();

    std::atomic_int mStatus = Idle;
    
    int mThreadNum = 4;
};

} // namespace obotcha
#endif
