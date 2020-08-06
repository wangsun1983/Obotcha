#ifndef __OBOTCHA_HTTP_V1_SERVER_HPP__
#define __OBOTCHA_HTTP_V1_SERVER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"
#include "TcpServer.hpp"
#include "HttpV1ClientInfo.hpp"
#include "Mutex.hpp"
#include "SocketListener.hpp"
#include "HttpV1ResponseWriter.hpp"
#include "HttpMultiPart.hpp"
#include "SSLServer.hpp"
#include "BlockingLinkedList.hpp"
#include "HashSet.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(DispatchHttpWorkData) {
public:
    _DispatchHttpWorkData(int,ByteArray);

    int fd;
    ByteArray pack;
};

DECLARE_SIMPLE_CLASS(HttpDispatchStatusListener) {
public:
    virtual void onComplete(int fd) = 0;
    virtual void lockData() = 0;
    virtual void unlockData() = 0;
};

DECLARE_SIMPLE_CLASS(HttpV1Listener) {
public:
    virtual void onMessage(HttpV1ClientInfo client,HttpV1ResponseWriter w,HttpPacket msg) = 0;
    virtual void onConnect(HttpV1ClientInfo) = 0;
    virtual void onDisconnect(HttpV1ClientInfo) = 0;
};

DECLARE_SIMPLE_CLASS(HttpDispatchThread) IMPLEMENTS(Thread) {
public:
    _HttpDispatchThread(HttpDispatchStatusListener,HttpV1Listener);
    void add(DispatchHttpWorkData);
    int getWorkQueueSize();
    void run();

private:
    BlockingLinkedList<DispatchHttpWorkData> datas;
    HttpDispatchStatusListener mListener;
    HttpV1Listener mV1Listener;
    HashSet<int> mWorkedFds;
};

DECLARE_SIMPLE_CLASS(HttpV1Server) IMPLEMENTS(HttpDispatchStatusListener),st(SocketListener) {

public:
    friend class _HttpV1SocketListener;
    
    _HttpV1Server(int port,HttpV1Listener,String certificate,String key);

    _HttpV1Server(int port,HttpV1Listener);

    _HttpV1Server(HttpV1Listener);

    _HttpV1Server(HttpV1Listener,String certificate,String key);

    _HttpV1Server(String ip,int port,HttpV1Listener);

    _HttpV1Server(String ip,int port,HttpV1Listener,String certificate,String key);

    void parseMessage(int fd,ByteArray);

    void addClient(int fd);

    void removeClient(int fd);

    void exit();

private:
    void onComplete(int fd);
    void lockData();
    void unlockData();

    void onDataReceived(SocketResponser r,ByteArray pack);

    void onDisconnect(SocketResponser r);

    void onConnect(SocketResponser r);

    void onTimeout();

    TcpServer mTcpServer;

    SSLServer mSSLServer;

    HttpV1Listener mHttpListener;

    String mIp;

    int mPort;

    HashMap<int,ByteArray> mBuffPool;

    int threadsNum;

    ArrayList<HttpDispatchThread> mThreads;

    Mutex mBuffPoolMutex;

    Mutex mMutex;

    HashMap<int,Integer> fdmaps;
};

}
#endif
