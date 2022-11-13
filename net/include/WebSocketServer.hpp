#ifndef __OBOTCHA_WEBSOCKET_SERVER_HPP__
#define __OBOTCHA_WEBSOCKET_SERVER_HPP__

#include <fstream>
#include <map>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <unordered_set>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "BlockingLinkedList.hpp"
#include "EPollFileObserver.hpp"
#include "HttpPacket.hpp"
#include "HttpServer.hpp"
#include "LinkedList.hpp"
#include "Mutex.hpp"
#include "Random.hpp"
#include "SocketListener.hpp"
#include "SpinLock.hpp"
#include "String.hpp"
#include "ThreadPoolExecutor.hpp"
#include "WebSocketLinker.hpp"
#include "WebSocketLinkerManager.hpp"
#include "WebSocketListener.hpp"
#include "WebSocketOption.hpp"
#include "WebSocketParser.hpp"
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
