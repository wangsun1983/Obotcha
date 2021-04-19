#ifndef __OBOTCHA_HTTP_URL_CONNECTION_POOL_HPP__
#define __OBOTCHA_HTTP_URL_CONNECTION_POOL_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketMonitor.hpp"
#include "HttpUrlConnection.hpp"
#include "HttpUrl.hpp"
#include "ThreadPoolExecutor.hpp"
#include "Mutex.hpp"
#include "Socket.hpp"

namespace obotcha {

class _HttpUrl;

DECLARE_SIMPLE_CLASS(HttpUrlAsyncConnectionPool) IMPLEMENTS(SocketListener){

public:
    _HttpUrlAsyncConnectionPool();
    HttpUrlConnection createConnection(HttpUrl url);
    void recyleConnection(HttpUrlConnection);
    void onSocketMessage(int,Socket,ByteArray);
private:
    Mutex mMutex;
    HashMap<Socket,HttpUrlConnection> mConnections;
    ThreadPoolExecutor mExecutor;
    SocketMonitor mSocketMonitor;
};

}
#endif
