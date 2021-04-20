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
    mConnections = createHashMap<Socket,HttpUrlAsyncConnection>();
    mExecutor = createExecutorBuilder()->newThreadPool();
}

HttpUrlAsyncConnection _HttpUrlAsyncConnectionPool::createConnection(HttpUrl url,HttpAsyncConnectionListener l,HttpOption o ) {
    HttpUrlAsyncConnection connection = createHttpUrlAsyncConnection(url,l,o);
    mExecutor->execute([](HttpUrlAsyncConnectionPool pool,HttpUrlAsyncConnection c) {
        int ret = c->connect();
        if(c->mListener != nullptr) {
            c->mListener->onConnect(ret);
        }

        {
            AutoLock l(pool->mMutex);
            pool->mConnections->put(c->mSocket,c);
            pool->mSocketMonitor->bind(c->mSocket,pool);
        }
    },AutoClone(this),connection);
    return connection;
}

void _HttpUrlAsyncConnectionPool::recyleConnection(HttpUrlAsyncConnection c) {
    {
        AutoLock l(mMutex);
        mConnections->remove(c->mSocket);
        mSocketMonitor->remove(c->mSocket);
    }
}

void _HttpUrlAsyncConnectionPool::onSocketMessage(int event,Socket s,ByteArray data) {
    AutoLock l(mMutex);
    HttpUrlAsyncConnection url = mConnections->get(s);
    if(url != nullptr) {
        url->onResponse(event,data);
    }
}

void _HttpUrlAsyncConnectionPool::release() {
    //TODO
}

}
