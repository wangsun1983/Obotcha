#ifndef __OBOTCHA_HTTP_URL_CONNECTION_POOL_HPP__
#define __OBOTCHA_HTTP_URL_CONNECTION_POOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketMonitor.hpp"
#include "HttpUrlAsyncConnection.hpp"
#include "HttpUrl.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Mutex.hpp"
#include "Socket.hpp"
#include "HttpUrl.hpp"
#include "HttpUrlAsyncConnection.hpp"
#include "HttpOption.hpp"

namespace obotcha {

class _HttpUrl;

DECLARE_SIMPLE_CLASS(HttpUrlAsyncConnectionPool) IMPLEMENTS(SocketListener){

public:
    _HttpUrlAsyncConnectionPool();
    HttpUrlAsyncConnection createConnection(HttpUrl url,HttpAsyncConnectionListener l,HttpOption o);
    void recyleConnection(HttpUrlAsyncConnection);
    void onSocketMessage(int,Socket,ByteArray);

    void release();
private:
    Mutex mMutex;
    HashMap<Socket,HttpUrlAsyncConnection> mConnections;
    ThreadPoolExecutor mExecutor;
    SocketMonitor mSocketMonitor;
};

}
#endif
