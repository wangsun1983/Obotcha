#ifndef __OBOTCHA_WEBSOCKET_SERVER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_HPP__

#include <atomic>

#include "Object.hpp"
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
    _WebSocketServer(InetAddress addr = nullptr,HttpOption option = nullptr,int threadnum = 4);

    int start();

    int close();

    void dump();

    int bind(String, WebSocketListener);

private:
    enum Status {
        Idle = 0,
        Running,
        Closed
    };

    void onHttpMessage(int, sp<_HttpLinker> client, HttpResponseWriter w,
                       HttpPacket msg);

    void onSocketMessage(int, Socket, ByteArray);

    WebSocketLinker createLinker(sp<_HttpLinker>,int ver);

    InetAddress mAddress;

    HttpServer mHttpServer;

    SocketMonitor mSocketMonitor;

    HashMap<String, WebSocketListener> mWsListeners;

    //WebSocketOption mWsOption;

    HttpOption mHttpOption;

    //WebSocketLinkerManager mLinkerManager;
    ConcurrentHashMap<Socket,sp<_WebSocketLinker>> mLinkers;

    //WebSocketInspector mInspector;

    std::atomic_int mStatus;
    
    int mThreadNum;
};

} // namespace obotcha
#endif
