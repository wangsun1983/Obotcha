#ifndef __OBOTCHA_HTTP_URL_CONNECTION_POOL_HPP__
#define __OBOTCHA_HTTP_URL_CONNECTION_POOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketMonitor.hpp"
#include "HttpUrl.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Mutex.hpp"
#include "Socket.hpp"
#include "HttpUrl.hpp"
#include "HttpOption.hpp"

namespace obotcha {

class _HttpAsyncConnection;
class _HttpConnectionListener;

DECLARE_SIMPLE_CLASS(HttpAsyncConnectionPool) IMPLEMENTS(SocketListener){

public:
    friend class _HttpAsyncConnection;

    _HttpAsyncConnectionPool();
    sp<_HttpAsyncConnection> createConnection(HttpUrl url,sp<_HttpConnectionListener> l,HttpOption o);
    void onSocketMessage(int,Socket,ByteArray);
    void close();

private:
    void recyleConnection(sp<_HttpAsyncConnection>);
    
    Mutex mMutex;
    HashMap<Socket,sp<_HttpAsyncConnection>> mConnections;
    ThreadPoolExecutor mExecutor;
    SocketMonitor mSocketMonitor;
};

}
#endif
