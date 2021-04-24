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

class _HttpUrlAsyncConnection;
class _HttpAsyncConnectionListener;

DECLARE_SIMPLE_CLASS(HttpUrlAsyncConnectionPool) IMPLEMENTS(SocketListener){

public:
    friend class _HttpUrlAsyncConnection;

    _HttpUrlAsyncConnectionPool();
    sp<_HttpUrlAsyncConnection> createConnection(HttpUrl url,sp<_HttpAsyncConnectionListener> l,HttpOption o);
    void onSocketMessage(int,Socket,ByteArray);
    void release();

private:
    void recyleConnection(sp<_HttpUrlAsyncConnection>);
    
    Mutex mMutex;
    HashMap<Socket,sp<_HttpUrlAsyncConnection>> mConnections;
    ThreadPoolExecutor mExecutor;
    SocketMonitor mSocketMonitor;
};

}
#endif
