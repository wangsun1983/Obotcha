#ifndef __OBOTCHA_HTTP__SERVER_HPP__
#define __OBOTCHA_HTTP__SERVER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "ServerSocket.hpp"
#include "SocketMonitor.hpp"
#include "HttpListener.hpp"
#include "HttpOption.hpp"
#include "CountDownLatch.hpp"

namespace obotcha {

DECLARE_CLASS(HttpServer) IMPLEMENTS(SocketListener) {

public:
    //friend class _HttpSocketListener;
    
    _HttpServer(InetAddress addr,HttpListener,HttpOption option = nullptr);

    int start();
    
    void remove(HttpLinker);
    
    void close();

    void join(long interval = 0);
    
    ~_HttpServer();

private:

    void onSocketMessage(int,Socket,ByteArray);

    //void http2FrameProcessor(HttpLinker info);

    ServerSocket mServerSock;

    SocketMonitor mSockMonitor;

    HttpListener mHttpListener;

    InetAddress mAddress;

    HttpOption mOption;

    //HttpLinkerManager mLinkerManager;
    ConcurrentHashMap<Socket,HttpLinker> mLinkers;

    CountDownLatch mExitLatch;
};

}
#endif
