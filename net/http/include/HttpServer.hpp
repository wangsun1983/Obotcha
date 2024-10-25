#ifndef __OBOTCHA_HTTP__SERVER_HPP__
#define __OBOTCHA_HTTP__SERVER_HPP__

#include "Object.hpp"
#include "SocketListener.hpp"
#include "ServerSocket.hpp"
#include "SocketMonitor.hpp"
#include "HttpListener.hpp"
#include "HttpOption.hpp"
#include "CountDownLatch.hpp"

namespace obotcha {

DECLARE_CLASS(HttpServer) IMPLEMENTS(SocketListener) {

public:
    _HttpServer(InetAddress addr,HttpListener,HttpOption option = nullptr);

    int start();
    
    void remove(HttpLinker);
    
    void close();

    void waitForExit(long interval = 0);
    
    ~_HttpServer() override;

private:

    void onSocketMessage(st(Net)::Event,Socket,ByteArray) override;

    ServerSocket mServerSock = nullptr;
    SocketMonitor mSockMonitor = nullptr;
    HttpListener mHttpListener;
    InetAddress mAddress;
    HttpOption mOption;
    ConcurrentHashMap<Socket,HttpLinker> mLinkers = ConcurrentHashMap<Socket,HttpLinker>::New();
    CountDownLatch mExitLatch = CountDownLatch::New(1);

    st(Net)::Protocol mProtocol = st(Net)::Protocol::Http;
};

}
#endif
