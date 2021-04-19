#include "Object.hpp"
#include "StrongPointer.hpp"

#include "SocketMonitor.hpp"
#include "ExecutorBuilder.hpp"
#include "HttpUrlAsyncConnectionPool.hpp"
#include "Handler.hpp"

namespace obotcha {

_HttpUrlAsyncConnectionPool::_HttpUrlAsyncConnectionPool() {
    mMutex = createMutex();
    mSocketMonitor = createSocketMonitor();
    mExecutor = createExecutorBuilder()->newThreadPool();
    mConnections = createHashMap<Socket,HttpUrlConnection>();
}

HttpUrlConnection _HttpUrlAsyncConnectionPool::createConnection(HttpUrl url) {
    HttpUrlConnection connection = createHttpUrlConnection(url,createHandler());
    
    mExecutor->execute([](HttpUrlConnection c,Mutex mutex,HashMap<Socket,HttpUrlConnection> map) {
        c->connect();
        {
            AutoLock l(mutex);
            map->put(c->mSocket,c);
        }
    },connection,mMutex,mConnections);

    return connection;
}

void _HttpUrlAsyncConnectionPool::recyleConnection(HttpUrlConnection c) {
    {
        AutoLock l(mMutex);
        mConnections->remove(c->mSocket);
    }
}

void _HttpUrlAsyncConnectionPool::onSocketMessage(int event,Socket s,ByteArray data) {
    AutoLock l(mMutex);
    HttpUrlConnection url = mConnections->get(s);
    if(url != nullptr) {
        url->onResponse(event,data);
    }
}

}
